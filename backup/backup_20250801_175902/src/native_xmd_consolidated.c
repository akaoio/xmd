/**
 * @file native_xmd_consolidated.c
 * @brief Consolidated native XMD parser implementation
 * @author XMD Development Team
 *
 * All native XMD functionality consolidated from 4 files.
 * Provides native syntax parsing, evaluation, and dispatching.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../include/native_xmd.h"
#include "../include/xmd_processor_internal.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/ast_node.h"
#include "../include/ast_parser.h"
#include "../include/ast_evaluator.h"

// GENESIS DIRECTIVE: STRING PARSER ELIMINATED - AST PARSER HANDLES ALL PROCESSING

// ============================================================================
// NATIVE XMD LEXER (FROM native_lexer.c)
// ============================================================================

/**
 * @brief Native XMD token types
 */
typedef enum {
    NATIVE_TOKEN_TEXT,
    NATIVE_TOKEN_VAR_START,
    NATIVE_TOKEN_VAR_END,
    NATIVE_TOKEN_DIRECTIVE_START,
    NATIVE_TOKEN_DIRECTIVE_END,
    NATIVE_TOKEN_IDENTIFIER,
    NATIVE_TOKEN_OPERATOR,
    NATIVE_TOKEN_STRING,
    NATIVE_TOKEN_NUMBER,
    NATIVE_TOKEN_EOF
} native_token_type;

/**
 * @brief Native XMD token structure
 */
typedef struct native_token {
    native_token_type type;
    char* value;
    int line;
    int column;
    struct native_token* next;
} native_token;

/**
 * @brief Create a new native token
 * @param type Token type
 * @param value Token value
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on error
 */
static native_token* native_token_create(native_token_type type, const char* value, int line, int column) {
    native_token* token = xmd_malloc(sizeof(native_token));
    if (!token) {
        return NULL;
    }
    
    token->type = type;
    token->value = value ? xmd_strdup(value) : NULL;
    token->line = line;
    token->column = column;
    token->next = NULL;
    
    return token;
}

/**
 * @brief Free native token list
 * @param head Head of token list
 */
static void native_token_free_list(native_token* head) {
    while (head) {
        native_token* next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

/**
 * @brief Check if text starts with a bare XMD keyword
 * @param text Text to check
 * @return Length of keyword if found, 0 otherwise
 */
static int is_bare_keyword(const char* text) {
    if (!text) return 0;
    
    const char* keywords[] = {
        "set ", "print ", "function ", "if ", "else ", "for ", "while ", 
        "const ", "let ", "return ", "break ", "continue ", NULL
    };
    
    for (int i = 0; keywords[i]; i++) {
        size_t len = strlen(keywords[i]) - 1; // Don't include trailing space
        if (strncmp(text, keywords[i], len + 1) == 0) {
            return len;
        }
    }
    
    return 0;
}

/**
 * @brief Tokenize native XMD syntax
 * @param input Input string
 * @return Token list or NULL on error
 */
native_token* native_lexer_tokenize(const char* input) {
    if (!input) {
        return NULL;
    }
    
    native_token* head = NULL;
    native_token* tail = NULL;
    
    int line = 1;
    int column = 1;
    const char* pos = input;
    
    bool at_line_start = true;
    
    while (*pos) {
        native_token* token = NULL;
        
        // Skip whitespace
        while (*pos == ' ' || *pos == '\t') {
            pos++;
            column++;
        }
        
        // Check for variable interpolation: {{var}} (Genesis preferred) or ${var} (legacy)
        if ((pos[0] == '{' && pos[1] == '{') || (pos[0] == '$' && pos[1] == '{')) {
            const char* var_start = (pos[0] == '{') ? "{{" : "${";
            token = native_token_create(NATIVE_TOKEN_VAR_START, var_start, line, column);
            pos += 2;
            column += 2;
            at_line_start = false;
        }
        // Check for directive: #xmd:directive
        else if (pos[0] == '#' && strncmp(pos, "#xmd:", 5) == 0) {
            token = native_token_create(NATIVE_TOKEN_DIRECTIVE_START, "#xmd:", line, column);
            pos += 5;
            column += 5;
            at_line_start = false;
        }
        // Check for bare keyword at line start
        else if (at_line_start) {
            int keyword_len = is_bare_keyword(pos);
            if (keyword_len > 0) {
                // Create directive start token with empty value for bare keywords
                token = native_token_create(NATIVE_TOKEN_DIRECTIVE_START, "", line, column);
                at_line_start = false;
                
                // Add the token to the list
                if (!head) {
                    head = tail = token;
                } else {
                    tail->next = token;
                    tail = token;
                }
                
                // Now read the entire directive line as TEXT
                const char* line_start = pos;
                while (*pos && *pos != '\n') {
                    column++;
                    pos++;
                }
                
                // Create directive text token with the full directive content
                if (pos > line_start) {
                    char* directive_text = xmd_malloc(pos - line_start + 1);
                    if (directive_text) {
                        strncpy(directive_text, line_start, pos - line_start);
                        directive_text[pos - line_start] = '\0';
                        token = native_token_create(NATIVE_TOKEN_TEXT, directive_text, line, column - (pos - line_start));
                        free(directive_text);
                    }
                }
                continue; // Skip normal token processing
            }
        }
        
        // Handle remaining cases if no token was created yet
        if (!token) {
            // Check for closing brace(s) - handle both }} and }
            if (*pos == '}') {
                // Check if it's }} (for {{var}} syntax)
                if (pos[1] == '}') {
                    token = native_token_create(NATIVE_TOKEN_VAR_END, "}}", line, column);
                    pos += 2;
                    column += 2;
                } else {
                    token = native_token_create(NATIVE_TOKEN_VAR_END, "}", line, column);
                    pos++;
                    column++;
                }
            }
            // Check for newline after directive
            else if (*pos == '\n') {
                token = native_token_create(NATIVE_TOKEN_DIRECTIVE_END, "\n", line, column);
                pos++;
                line++;
                column = 1;
                at_line_start = true;
            }
            // Read text content
            else {
                const char* start = pos;
                while (*pos && *pos != '$' && *pos != '#' && *pos != '}' && *pos != '{' && *pos != '\n') {
                    column++;
                    pos++;
                }
                
                if (pos > start) {
                    char* text = xmd_malloc(pos - start + 1);
                    if (text) {
                        strncpy(text, start, pos - start);
                        text[pos - start] = '\0';
                        token = native_token_create(NATIVE_TOKEN_TEXT, text, line, column - (pos - start));
                        free(text);
                    }
                }
            }
        }
        
        // Add token to list
        if (token) {
            if (!head) {
                head = tail = token;
            } else {
                tail->next = token;
                tail = token;
            }
        }
    }
    
    // Add EOF token
    native_token* eof = native_token_create(NATIVE_TOKEN_EOF, "", line, column);
    if (eof) {
        if (!head) {
            head = eof;
        } else {
            tail->next = eof;
        }
    }
    
    return head;
}

// ============================================================================
// NATIVE XMD PARSER (FROM native_parser.c)
// ============================================================================

/**
 * @brief Native XMD AST node types
 */
typedef enum {
    NATIVE_AST_DOCUMENT,
    NATIVE_AST_TEXT,
    NATIVE_AST_VARIABLE,
    NATIVE_AST_DIRECTIVE,
    NATIVE_AST_EXPRESSION
} native_ast_type;

/**
 * @brief Native XMD AST node
 */
typedef struct native_ast_node {
    native_ast_type type;
    char* value;
    struct native_ast_node* children;
    struct native_ast_node* next;
} native_ast_node;

/**
 * @brief Create native AST node
 * @param type Node type
 * @param value Node value
 * @return New node or NULL on error
 */
static native_ast_node* native_ast_create(native_ast_type type, const char* value) {
    native_ast_node* node = xmd_malloc(sizeof(native_ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = type;
    node->value = value ? xmd_strdup(value) : NULL;
    node->children = NULL;
    node->next = NULL;
    
    return node;
}

/**
 * @brief Free native AST tree
 * @param node Root node
 */
static void native_ast_free(native_ast_node* node) {
    if (!node) {
        return;
    }
    
    native_ast_free(node->children);
    native_ast_free(node->next);
    free(node->value);
    free(node);
}

/**
 * @brief Parse native XMD tokens into AST
 * @param tokens Token list
 * @return AST root or NULL on error
 */
native_ast_node* native_parser_parse(native_token* tokens) {
    if (!tokens) {
        return NULL;
    }
    
    native_ast_node* document = native_ast_create(NATIVE_AST_DOCUMENT, NULL);
    if (!document) {
        return NULL;
    }
    
    native_ast_node* current_child = NULL;
    native_token* token = tokens;
    
    while (token && token->type != NATIVE_TOKEN_EOF) {
        native_ast_node* node = NULL;
        
        switch (token->type) {
            case NATIVE_TOKEN_TEXT:
                node = native_ast_create(NATIVE_AST_TEXT, token->value);
                break;
                
            case NATIVE_TOKEN_VAR_START:
                // Parse variable reference
                token = token->next;
                if (token && token->type == NATIVE_TOKEN_TEXT) {
                    node = native_ast_create(NATIVE_AST_VARIABLE, token->value);
                    token = token->next;
                    // Skip closing brace
                    if (token && token->type == NATIVE_TOKEN_VAR_END) {
                        token = token->next;
                    }
                }
                continue;
                
            case NATIVE_TOKEN_DIRECTIVE_START:
                // Parse directive
                token = token->next;
                if (token && token->type == NATIVE_TOKEN_TEXT) {
                    node = native_ast_create(NATIVE_AST_DIRECTIVE, token->value);
                    token = token->next;
                    // Skip to end of line
                    while (token && token->type != NATIVE_TOKEN_DIRECTIVE_END) {
                        token = token->next;
                    }
                }
                break;
                
            default:
                break;
        }
        
        if (node) {
            if (!document->children) {
                document->children = current_child = node;
            } else {
                current_child->next = node;
                current_child = node;
            }
        }
        
        if (token) {
            token = token->next;
        }
    }
    
    return document;
}

// ============================================================================
// NATIVE XMD EVALUATOR (FROM native_evaluator.c)
// ============================================================================

/**
 * @brief Evaluate native XMD AST node
 * @param node AST node
 * @param ctx Processor context
 * @param output Output buffer
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
static int native_evaluate_node(native_ast_node* node, processor_context* ctx, 
                               char* output, size_t output_size) {
    if (!node || !output) {
        return -1;
    }
    
    size_t written = 0;
    
    switch (node->type) {
        case NATIVE_AST_TEXT:
            if (node->value) {
                size_t len = strlen(node->value);
                if (written + len < output_size) {
                    strcpy(output + written, node->value);
                    written += len;
                }
            }
            break;
            
        case NATIVE_AST_VARIABLE:
            if (node->value && ctx && ctx->variables) {
                variable* var = store_get(ctx->variables, node->value);
                if (var) {
                    const char* value = variable_to_string(var);
                    if (value) {
                        size_t len = strlen(value);
                        if (written + len < output_size) {
                            strcpy(output + written, value);
                            written += len;
                        }
                    }
                }
            }
            break;
            
        case NATIVE_AST_DIRECTIVE:
            // Process directive (simplified)
            if (node->value && strncmp(node->value, "set ", 4) == 0) {
                // Variable assignment: set name "value"
                // Make a copy to avoid modifying the original
                char* assignment_copy = xmd_strdup(node->value + 4);
                if (assignment_copy) {
                    // Find first space to separate key from value
                    char* space = strchr(assignment_copy, ' ');
                    if (space) {
                        *space = '\0';
                        char* key = assignment_copy;
                        char* value = space + 1;
                        
                        // Trim whitespace from key
                        while (*key == ' ') key++;
                        
                        // Trim whitespace and quotes from value
                        while (*value == ' ') value++;
                        if (*value == '"' && value[strlen(value)-1] == '"') {
                            value++;
                            value[strlen(value)-1] = '\0';
                        }
                        
                        if (ctx && ctx->variables) {
                            variable* var = variable_create_string(value);
                            if (var) {
                                store_set(ctx->variables, key, var);
                            }
                        }
                    }
                    free(assignment_copy);
                }
            }
            break;
            
        case NATIVE_AST_DOCUMENT:
            // Process all children
            {
                native_ast_node* child = node->children;
                while (child) {
                    native_evaluate_node(child, ctx, output + written, output_size - written);
                    written = strlen(output);
                    child = child->next;
                }
            }
            break;
            
        default:
            break;
    }
    
    return 0;
}

/**
 * @brief Evaluate native XMD AST
 * @param ast AST root
 * @param ctx Processor context
 * @return Output string or NULL on error
 */
char* native_evaluator_evaluate(native_ast_node* ast, processor_context* ctx) {
    if (!ast) {
        return NULL;
    }
    
    // Allocate output buffer
    size_t output_size = 65536; // 64KB initial size
    char* output = xmd_malloc(output_size);
    if (!output) {
        return NULL;
    }
    
    output[0] = '\0';
    
    // Evaluate AST
    if (native_evaluate_node(ast, ctx, output, output_size) != 0) {
        free(output);
        return NULL;
    }
    
    return output;
}

// ============================================================================
// XMD DISPATCHER (FROM xmd_dispatcher.c)
// ============================================================================

// Removed old xmd_dispatch_process implementation - duplicate function removed
// per Developer2 tech debt consolidation (Genesis NO DUPLICATES directive)

/**
 * @brief Process native XMD file
 * @param filename File path
 * @param ctx Processor context
 * @return Processed output or NULL on error
 */
char* native_xmd_process_file(const char* filename, processor_context* ctx) {
    if (!filename) {
        return NULL;
    }
    
    // Read file content
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = xmd_malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    
    // Process content using PURE AST (Genesis directive: NO STRING PARSER)
    char* output = ast_process_xmd_content(content, ctx->variables);
    free(content);
    
    return output;
}

// ============================================================================
// NATIVE XMD PUBLIC API
// ============================================================================

/**
 * @brief Initialize native XMD processor
 * @return 0 on success, -1 on error
 */
int native_xmd_init(void) {
    // Initialize native XMD system
    return 0;
}

/**
 * @brief Cleanup native XMD processor
 */
void native_xmd_cleanup(void) {
    // Cleanup native XMD system
}

/**
 * @brief Get native XMD version
 * @return Version string
 */
const char* native_xmd_get_version(void) {
    return "Native XMD v1.0 (consolidated)";
}

// ============================================================================
// PROCESSOR FUNCTIONS (REAL IMPLEMENTATIONS)
// ============================================================================

/**
 * @brief Process XMD string content (real implementation)
 * @param processor Processor instance
 * @param input Input string
 * @param length Input length
 * @return Result or NULL on error
 */
// Renamed to avoid conflict with bindings_consolidated.c implementation
// This is the native XMD-specific processor that works with bare store*
static xmd_result* native_xmd_process_string_internal(xmd_processor* processor, const char* input, size_t length) {
    (void)length; // Unused parameter
    if (!input || !processor) {
        return NULL;
    }
    
    xmd_result* result = xmd_malloc(sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    // Initialize result
    result->error_code = XMD_SUCCESS;
    result->error_message = NULL;
    result->processing_time_ms = 0;
    result->memory_used_bytes = 0;
    
    // Use processor as the variable store directly (it's a store* cast as xmd_processor*)
    store* variables = (store*)processor;
    
    // Create context using the processor's store
    processor_context ctx = {0};
    ctx.variables = variables;
    
    // Process using REAL AST parser (Genesis directive: NO STRING PARSER)
    result->output = ast_process_xmd_content(input, variables);
    if (!result->output) {
        // Fallback: return copy of input if processing fails
        result->output = xmd_strdup(input);
        if (!result->output) {
            result->error_code = XMD_ERROR_OUT_OF_MEMORY;
            result->error_message = xmd_strdup("Memory allocation failed");
            return result;
        }
    }
    
    result->output_length = result->output ? strlen(result->output) : 0;
    result->memory_used_bytes = sizeof(xmd_result) + result->output_length + 1;
    
    return result;
}

// STRING PARSER ELIMINATED PER GENESIS DIRECTIVE: "COMPLETELY REMOVE THE STRING PARSER"
// Former xmd_dispatch_process() function removed - AST parser handles all processing

/**
 * @brief Process XMD content using REAL AST (per Genesis "DONOT FAKE THE AST PARSER")
 * @param input Input content
 * @param variables Variable store
 * @return Processed output or NULL on error
 */
char* ast_process_xmd_content(const char* input, store* variables) {
    if (!input) {
        return NULL;
    }
    
    // PHASE 1: Parse to REAL AST (no string processing fallback per Genesis directive)
    ast_node* program = ast_parse_program(input);
    if (!program) {
        // Genesis directive: NO STRING PARSER - AST parser must handle all cases
        return xmd_strdup(""); // Return empty string if parsing fails
    }
    
    // PHASE 2: Create separate variables store for AST evaluator
    // FIX: Don't pass processor variables directly to avoid double-free bug
    store* eval_variables = store_create();
    if (!eval_variables) {
        ast_free(program);
        return xmd_strdup("Memory allocation error");
    }
    
    // Copy variables from processor store to evaluator store
    if (variables) {
        // Iterate through all keys in the processor's variables store
        size_t key_count = 0;
        char** keys = store_keys(variables, &key_count);
        if (keys) {
            for (size_t i = 0; i < key_count; i++) {
                variable* var = store_get(variables, keys[i]);
                if (var) {
                    // Reference the variable and add to evaluator store
                    variable_ref(var);
                    store_set(eval_variables, keys[i], var);
                }
            }
            free(keys);
        }
    }
    
    // Create AST evaluation context with separate variables store
    ast_evaluator* evaluator = ast_evaluator_create(eval_variables, NULL);
    if (!evaluator) {
        store_destroy(eval_variables);
        ast_free(program);
        return xmd_strdup("Memory allocation error");
    }
    
    // PHASE 3: Evaluate AST program (Genesis: PURE AST - NO STRING FALLBACK)
    char* output = ast_evaluate_program(program, evaluator);
    if (!output) {
        // Genesis directive: NO STRING PARSER - Must work with AST only
        output = xmd_strdup(""); // Return empty string if evaluation fails
    }
    
    // PHASE 4: Cleanup (now safe - evaluator owns its variables store)
    ast_evaluator_free(evaluator); // This will destroy eval_variables safely
    ast_free(program);
    
    return output;
}

/**
 * @brief Evaluate AST program node and generate output
 * @param program AST program node
 * @param evaluator AST evaluator context
 * @return Generated output string or NULL on error
 */
char* ast_evaluate_program(ast_node* program, ast_evaluator* evaluator) {
    if (!program || program->type != AST_PROGRAM || !evaluator) {
        return NULL;
    }
    
    // Initialize output buffer
    size_t output_size = 1024;
    char* output = xmd_malloc(output_size);
    if (!output) return NULL;
    
    size_t output_pos = 0;
    output[0] = '\0';
    
    // Process each statement in the program
    for (size_t i = 0; i < program->data.program.statement_count; i++) {
        ast_node* stmt = program->data.program.statements[i];
        if (!stmt) continue;
        
        // Evaluate statement
        ast_value* result = ast_evaluate(stmt, evaluator);
        
        // Convert result to string if needed, but skip output for assignments
        if (result && stmt->type != AST_ASSIGNMENT) {
            const char* result_str = ast_value_to_string(result);
            if (result_str) {
                size_t result_len = strlen(result_str);
                
                // Ensure buffer is large enough
                while (output_pos + result_len + 2 >= output_size) {
                    output_size *= 2;
                    char* new_output = realloc(output, output_size);
                    if (!new_output) {
                        free(output);
                        ast_value_free(result);
                        return NULL;
                    }
                    output = new_output;
                }
                
                // Append result to output
                strcat(output + output_pos, result_str);
                output_pos += result_len;
                
                // Add newline for non-assignment statements
                strcat(output + output_pos, "\n");
                output_pos += 1;
            }
        }
        
        // Always free the result
        if (result) {
            ast_value_free(result);
        }
    }
    
    return output;
}

/**
 * @brief Evaluate a single AST statement
 * @param stmt AST statement node
 * @param evaluator AST evaluator context
 * @return AST value result or NULL
 */
ast_value* ast_evaluate_statement(ast_node* stmt, ast_evaluator* evaluator) {
    if (!stmt || !evaluator) {
        return NULL;
    }
    
    switch (stmt->type) {
        case AST_ASSIGNMENT:
            // For assignments, we need to return a value but assignments return int
            // Use the general evaluator which handles this correctly
            return ast_evaluate(stmt, evaluator);
        
        case AST_BINARY_OP:
            return ast_evaluate_binary_op(stmt, evaluator);
        
        case AST_IDENTIFIER:
            return ast_evaluate_identifier(stmt, evaluator);
        
        case AST_LITERAL:
            if (stmt->data.literal.type == LITERAL_STRING) {
                return ast_value_create_string(stmt->data.literal.value.string_value);
            } else if (stmt->data.literal.type == LITERAL_NUMBER) {
                return ast_value_create_number(stmt->data.literal.value.number_value);
            } else if (stmt->data.literal.type == LITERAL_BOOLEAN) {
                return ast_value_create_boolean(stmt->data.literal.value.boolean_value);
            }
            return NULL;
        
        default:
            return NULL;
    }
}

/**
 * @brief Evaluate assignment statement
 */
ast_value* ast_evaluate_assignment_real(ast_node* stmt, ast_evaluator* evaluator) {
    if (stmt->type != AST_ASSIGNMENT || !evaluator) {
        return NULL;
    }
    
    // Evaluate the right-hand side expression
    ast_value* value = ast_evaluate(stmt->data.assignment.value, evaluator);
    if (!value) {
        return NULL;
    }
    
    // Store in variables
    const char* var_name = stmt->data.assignment.variable;
    if (var_name && evaluator->variables) {
        variable* var = NULL;
        
        if (value->type == AST_VAL_STRING) {
            var = variable_create_string(value->value.string_value);
        } else if (value->type == AST_VAL_NUMBER) {
            var = variable_create_number(value->value.number_value);
        }
        
        if (var) {
            store_set(evaluator->variables, var_name, var);
        }
    }
    
    return value; // Return the assigned value
}

/**
 * @brief Evaluate binary operation (math expressions)
 */
ast_value* ast_evaluate_binary_op_real(ast_node* expr, ast_evaluator* evaluator) {
    if (expr->type != AST_BINARY_OP || !evaluator) {
        return NULL;
    }
    
    // Evaluate left and right operands
    ast_value* left = ast_evaluate(expr->data.binary_op.left, evaluator);
    ast_value* right = ast_evaluate(expr->data.binary_op.right, evaluator);
    
    if (!left || !right) {
        if (left) ast_value_free(left);
        if (right) ast_value_free(right);
        return NULL;
    }
    
    ast_value* result = NULL;
    
    // Perform operation based on operator
    if (expr->data.binary_op.op == BINOP_ADD) {
        if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
            double sum = left->value.number_value + right->value.number_value;
            result = ast_value_create_number(sum);
        }
    }
    // TODO: Add other operators (subtract, multiply, divide, etc.)
    
    ast_value_free(left);
    ast_value_free(right);
    
    return result;
}

/**
 * @brief Evaluate identifier (variable reference)
 */
ast_value* ast_evaluate_identifier_real(ast_node* expr, ast_evaluator* evaluator) {
    if (expr->type != AST_IDENTIFIER || !evaluator || !evaluator->variables) {
        return NULL;
    }
    
    const char* var_name = expr->data.identifier.name;
    variable* var = store_get(evaluator->variables, var_name);
    
    if (!var) {
        return ast_value_create_string(""); // Return empty string for undefined variables
    }
    
    // Convert variable to AST value
    const char* var_str = variable_to_string(var);
    if (var_str) {
        return ast_value_create_string(var_str);
    }
    
    return ast_value_create_string("");
}

