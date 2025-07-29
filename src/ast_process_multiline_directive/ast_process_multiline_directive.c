/**
 * @file ast_process_multiline_directive.c
 * @brief Process multiline XMD directives
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/xmd_processor_internal.h"

/**
 * @brief Check if content contains a function definition
 * @param content Directive content
 * @return 1 if function definition found, 0 otherwise
 */
static int is_function_definition(const char* content) {
    // Skip whitespace
    while (*content && isspace(*content)) content++;
    
    // Check if it starts with "function"
    return strncmp(content, "function", 8) == 0 && 
           (content[8] == ' ' || content[8] == '\t');
}

/**
 * @brief Extract function definition from multiline content
 * @param content Multiline directive content
 * @param func_name Output: function name (caller must free)
 * @param func_params Output: function parameters (caller must free)
 * @param func_body Output: function body (caller must free)
 * @return 0 on success, -1 on error
 */
static int parse_multiline_function(const char* content,
                                   char** func_name,
                                   char** func_params,
                                   char** func_body) {
    if (!content || !func_name || !func_params || !func_body) {
        return -1;
    }
    
    *func_name = NULL;
    *func_params = NULL;
    *func_body = NULL;
    
    // Skip to "function" keyword
    const char* ptr = content;
    while (*ptr && isspace(*ptr)) ptr++;
    
    if (strncmp(ptr, "function", 8) != 0) {
        return -1;
    }
    ptr += 8;
    
    // Skip whitespace after "function"
    while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
    
    // Extract function name
    const char* name_start = ptr;
    while (*ptr && !isspace(*ptr)) ptr++;
    
    size_t name_len = ptr - name_start;
    if (name_len == 0) return -1;
    
    *func_name = malloc(name_len + 1);
    if (!*func_name) return -1;
    memcpy(*func_name, name_start, name_len);
    (*func_name)[name_len] = '\0';
    
    // Extract parameters (rest of the first line)
    while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
    
    const char* params_start = ptr;
    while (*ptr && *ptr != '\n') ptr++;
    
    size_t params_len = ptr - params_start;
    *func_params = malloc(params_len + 1);
    if (!*func_params) {
        free(*func_name);
        *func_name = NULL;
        return -1;
    }
    memcpy(*func_params, params_start, params_len);
    (*func_params)[params_len] = '\0';
    
    // Skip newline
    if (*ptr == '\n') ptr++;
    
    // Rest is the function body
    *func_body = strdup(ptr);
    if (!*func_body) {
        free(*func_name);
        free(*func_params);
        *func_name = NULL;
        *func_params = NULL;
        return -1;
    }
    
    return 0;
}

/**
 * @brief Process a multiline XMD directive
 * @param content Multiline content (without <!-- xmd: and -->)
 * @param ctx Processor context
 * @return Processed result or NULL on error
 */
char* ast_process_multiline_directive(const char* content, processor_context* ctx) {
    if (!content || !ctx) {
        return NULL;
    }
    
    // Create evaluator for this multiline block
    ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
    if (!evaluator) {
        return strdup("");
    }
    
    // Check if this is a function definition
    if (is_function_definition(content)) {
        char* func_name = NULL;
        char* func_params = NULL;
        char* func_body = NULL;
        
        if (parse_multiline_function(content, &func_name, &func_params, &func_body) == 0) {
            // TODO: Function definition AST not yet implemented
            // Skip function definition handling for now
            /*
            source_location loc = {1, 1, "xmd_multiline"};
            ast_node* func_def = ast_create_function_def(func_name, loc);
            
            if (func_def) {
                // Add parameters
                char* params_copy = strdup(func_params);
                char* param = strtok(params_copy, " \t");
                while (param) {
                    ast_add_parameter(func_def, param);
                    param = strtok(NULL, " \t");
                }
                free(params_copy);
                
                // Parse function body
                // Split body into lines and process each
                ast_node* body_block = ast_create_block(loc);
                
                char* body_copy = strdup(func_body);
                char* line = strtok(body_copy, "\n");
                
                while (line) {
                    // Skip empty lines and leading whitespace
                    while (*line && isspace(*line)) line++;
                    
                    if (*line) {
                        // Tokenize and parse each line
                        token* tokens = lexer_enhanced_tokenize(line, "function_body");
                        if (tokens) {
                            ast_node* stmt_ast = ast_parse_program(tokens);
                            token_list_free(tokens);
                            
                            if (stmt_ast && stmt_ast->type == AST_PROGRAM && 
                                stmt_ast->data.program.statement_count > 0) {
                                // Add statement to function body
                                for (size_t i = 0; i < stmt_ast->data.program.statement_count; i++) {
                                    ast_node* stmt = stmt_ast->data.program.statements[i];
                                    // Detach statement from program to avoid double-free
                                    stmt_ast->data.program.statements[i] = NULL;
                                    ast_add_statement(body_block, stmt);
                                }
                            }
                            if (stmt_ast) ast_free(stmt_ast);
                        }
                    }
                    
                    line = strtok(NULL, "\n");
                }
                
                free(body_copy);
                
                // Set function body
                func_def->data.function_def.body = body_block;
                
                // Register the function in the evaluator
                int reg_status = ast_evaluator_register_function(evaluator, func_def);
                
                // Also register globally in processor context
                if (reg_status == 0 && ctx) {
                    // Grow the global functions array
                    size_t new_count = ctx->global_function_count + 1;
                    ast_node** new_functions = realloc(ctx->global_functions,
                                                      new_count * sizeof(ast_node*));
                    if (new_functions) {
                        new_functions[new_count - 1] = func_def;
                        ctx->global_functions = new_functions;
                        ctx->global_function_count = new_count;
                    }
                }
                
                // Don't free func_def as it's stored in evaluator
            }
            */
            
            free(func_name);
            free(func_params);
            free(func_body);
            
            // Return empty string for function definition
            return strdup("");
        }
    }
    
    // For non-function multiline directives, process each line separately
    char* result = malloc(1);
    result[0] = '\0';
    size_t result_len = 0;
    
    
    char* content_copy = strdup(content);
    char* line = strtok(content_copy, "\n");
    
    while (line) {
        // Skip empty lines and whitespace
        while (*line && isspace(*line)) line++;
        
        if (*line) {
            
            // Handle "set" directive specially
            if (strncmp(line, "set ", 4) == 0) {
                // Remove "set " prefix for assignment parsing
                line += 4;
                while (*line == ' ' || *line == '\t') line++;
            }
            
            // Process each line as a separate directive
            // Apply shell-style function transformation to each line
            // This converts "print text" to "print(text)" for proper AST parsing
            extern char* ast_transform_shell_function_call(const char* input);
            char* transformed = ast_transform_shell_function_call(line);
            const char* line_to_process = transformed ? transformed : line;
            token* tokens = lexer_enhanced_tokenize(line_to_process, "xmd_directive");
            if (tokens) {
                ast_node* ast = ast_parse_program(tokens);
                token_list_free(tokens);
                
                if (ast) {
                    // Check if it's an assignment
                    if (ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
                        ast_node* stmt = ast->data.program.statements[0];
                        if (stmt->type == AST_ASSIGNMENT) {
                            ast_evaluate_assignment(stmt, evaluator);
                        } else {
                            // Store current output buffer position
                            size_t prev_output_size = evaluator->output_size;
                            
                            ast_value* value = ast_evaluate(stmt, evaluator);
                            
                            // Check if evaluator's output buffer has grown (e.g., from print)
                            if (evaluator->output_size > prev_output_size) {
                                // Extract the new output
                                size_t new_output_len = evaluator->output_size - prev_output_size;
                                char* new_output = evaluator->output_buffer + prev_output_size;
                                
                                // Append to result
                                result = realloc(result, result_len + new_output_len + 2);
                                if (result) {
                                    memcpy(result + result_len, new_output, new_output_len);
                                    result_len += new_output_len;
                                    // Add newline after each print
                                    result[result_len++] = '\n';
                                    result[result_len] = '\0';
                                }
                            } else if (value) {
                                // Handle non-print expressions
                                if (value->type == AST_VAL_STRING && value->value.string_value) {
                                    size_t val_len = strlen(value->value.string_value);
                                    result = realloc(result, result_len + val_len + 2);
                                    if (result) {
                                        strcpy(result + result_len, value->value.string_value);
                                        result_len += val_len;
                                        result[result_len++] = '\n';
                                        result[result_len] = '\0';
                                    }
                                }
                            }
                            
                            if (value) ast_value_free(value);
                        }
                    }
                    ast_free(ast);
                }
            }
            
            // Free transformed string if it was allocated
            if (transformed) {
                free(transformed);
            }
        }
        
        line = strtok(NULL, "\n");
    }
    
    free(content_copy);
    
    // Remove trailing newline if present
    if (result_len > 0 && result[result_len-1] == '\n') {
        result[result_len-1] = '\0';
    }
    
    
    ast_evaluator_free(evaluator);
    return result;
}