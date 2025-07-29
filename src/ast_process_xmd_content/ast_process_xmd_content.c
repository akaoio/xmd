/**
 * @file ast_process_xmd_content.c
 * @brief AST-based XMD content processor
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/xmd_processor_internal.h"

// Function declarations
extern char* ast_substitute_variables(const char* text, store* variables);
extern const char* xmd_get_current_file_path(void);

/**
 * @brief Process XMD directive found in HTML comment
 * @param directive_content Content between <!-- xmd: and -->
 * @param ctx Processor context
 * @param output Output buffer for generated content
 * @param output_capacity Current capacity of output buffer
 * @param output_pos Current position in output buffer
 * @return 0 on success, -1 on error
 */
static int ast_process_directive_content(const char* directive_content, 
                                        processor_context* ctx,
                                        char** output,
                                        size_t* output_capacity,
                                        size_t* output_pos) {
    if (!directive_content || !ctx || !output || !output_capacity || !output_pos) {
        return -1;
    }
    
    // Skip "xmd:" prefix if present
    const char* content = directive_content;
    if (strncmp(content, "xmd:", 4) == 0) {
        content += 4;
        while (*content == ' ' || *content == '\t') content++;
    }
    
    // Check for special directives that need transformation to function calls
    if (strncmp(content, "set ", 4) == 0) {
        // "set" directive is already in assignment format, just parse it
        const char* assignment = content + 4;
        while (*assignment == ' ' || *assignment == '\t') assignment++;
        
        // Tokenize and parse
        token* tokens = lexer_enhanced_tokenize(assignment, "xmd_directive");
        if (!tokens) {
            return -1;
        }
        
        ast_node* ast = ast_parse_program(tokens);
        token_list_free(tokens);
        
        if (!ast) {
            return -1;
        }
        
        ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
        if (!evaluator) {
            ast_free(ast);
            return -1;
        }
        
        // Process assignment
        if (ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
            ast_node* stmt = ast->data.program.statements[0];
            if (stmt->type == AST_ASSIGNMENT) {
                ast_evaluate_assignment(stmt, evaluator);
            }
        }
        
        ast_evaluator_free(evaluator);
        ast_free(ast);
        return 0;
    }
    else if (strncmp(content, "import ", 7) == 0) {
        // Transform "import filename" to "import(filename)" for AST parsing
        const char* filename_start = content + 7;
        while (*filename_start == ' ' || *filename_start == '\t') filename_start++;
        
        
        // Remove quotes if present
        size_t filename_len = strlen(filename_start);
        char* filename = malloc(filename_len + 1);
        if (!filename) return -1;
        
        if ((filename_start[0] == '"' && filename_start[filename_len-1] == '"') ||
            (filename_start[0] == '\'' && filename_start[filename_len-1] == '\'')) {
            // Remove surrounding quotes
            memcpy(filename, filename_start + 1, filename_len - 2);
            filename[filename_len - 2] = '\0';
        } else {
            strcpy(filename, filename_start);
        }
        
        // Transform to function call format
        size_t transformed_len = strlen(filename) + 20;
        char* transformed = malloc(transformed_len);
        if (!transformed) {
            free(filename);
            return -1;
        }
        snprintf(transformed, transformed_len, "import(\"%s\")", filename);
        free(filename);
        
        // Use transformed content
        token* tokens = lexer_enhanced_tokenize(transformed, "xmd_directive");
        free(transformed);
        
        if (!tokens) {
            return -1;
        }
        
        // Parse and evaluate
        ast_node* ast = ast_parse_program(tokens);
        token_list_free(tokens);
        
        if (!ast) {
            return -1;
        }
        
        ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
        if (!evaluator) {
            ast_free(ast);
            return -1;
        }
        
        // Evaluate the function call
        if (ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
            ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
            if (result && result->type == AST_VAL_STRING && result->value.string_value) {
                // For import directive, write the result to output
                size_t result_len = strlen(result->value.string_value);
                size_t required = *output_pos + result_len;
                if (required >= *output_capacity) {
                    *output_capacity = required * 2;
                    *output = realloc(*output, *output_capacity);
                    if (!*output) {
                        ast_value_free(result);
                        ast_evaluator_free(evaluator);
                        ast_free(ast);
                        return -1;
                    }
                }
                memcpy(*output + *output_pos, result->value.string_value, result_len);
                *output_pos += result_len;
            }
            if (result) {
                ast_value_free(result);
            }
        }
        
        // Get any output generated by the evaluator (shouldn't be any for import, but check anyway)
        if (evaluator->output_buffer && evaluator->output_size > 0) {
            size_t required = *output_pos + evaluator->output_size;
            if (required >= *output_capacity) {
                *output_capacity = required * 2;
                *output = realloc(*output, *output_capacity);
                if (!*output) {
                    ast_evaluator_free(evaluator);
                    ast_free(ast);
                    return -1;
                }
            }
            memcpy(*output + *output_pos, evaluator->output_buffer, evaluator->output_size);
            *output_pos += evaluator->output_size;
        }
        
        ast_evaluator_free(evaluator);
        ast_free(ast);
        return 0;
    }
    else if (strncmp(content, "exec ", 5) == 0) {
        // Transform "exec command" to "exec(command)" for AST parsing
        const char* cmd_start = content + 5;
        while (*cmd_start == ' ' || *cmd_start == '\t') cmd_start++;
        
        // Need to properly quote the command
        size_t cmd_len = strlen(cmd_start);
        size_t new_len = cmd_len * 2 + 20; // exec("") + null + escapes
        char* transformed = malloc(new_len);
        if (!transformed) return -1;
        
        // If command already has quotes, use as-is; otherwise add quotes
        if ((cmd_start[0] == '"' && cmd_start[cmd_len-1] == '"') ||
            (cmd_start[0] == '\'' && cmd_start[cmd_len-1] == '\'')) {
            snprintf(transformed, new_len, "exec(%s)", cmd_start);
        } else {
            // Need to escape the command for string literal
            char* escaped_cmd = malloc(cmd_len * 2 + 1);
            if (!escaped_cmd) {
                free(transformed);
                return -1;
            }
            
            size_t j = 0;
            for (size_t i = 0; i < cmd_len; i++) {
                if (cmd_start[i] == '"') {
                    escaped_cmd[j++] = '\\';
                }
                escaped_cmd[j++] = cmd_start[i];
            }
            escaped_cmd[j] = '\0';
            
            snprintf(transformed, new_len, "exec(\"%s\")", escaped_cmd);
            free(escaped_cmd);
        }
        
        // Use transformed content
        token* tokens = lexer_enhanced_tokenize(transformed, "xmd_directive");
        free(transformed);
        
        if (!tokens) {
            return -1;
        }
        
        // Parse and evaluate
        ast_node* ast = ast_parse_program(tokens);
        token_list_free(tokens);
        
        if (!ast) {
            return -1;
        }
        
        ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
        if (!evaluator) {
            ast_free(ast);
            return -1;
        }
        
        // Evaluate the function call
        if (ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
            ast_value* result = ast_evaluate(ast->data.program.statements[0], evaluator);
            if (result && result->type == AST_VAL_STRING && result->value.string_value) {
                // For exec directive, write the result to output
                size_t result_len = strlen(result->value.string_value);
                size_t required = *output_pos + result_len;
                if (required >= *output_capacity) {
                    *output_capacity = required * 2;
                    *output = realloc(*output, *output_capacity);
                    if (!*output) {
                        ast_value_free(result);
                        ast_evaluator_free(evaluator);
                        ast_free(ast);
                        return -1;
                    }
                }
                memcpy(*output + *output_pos, result->value.string_value, result_len);
                *output_pos += result_len;
            }
            if (result) {
                ast_value_free(result);
            }
        }
        
        // Get any output generated
        if (evaluator->output_buffer && evaluator->output_size > 0) {
            size_t required = *output_pos + evaluator->output_size;
            if (required >= *output_capacity) {
                *output_capacity = required * 2;
                *output = realloc(*output, *output_capacity);
                if (!*output) {
                    ast_evaluator_free(evaluator);
                    ast_free(ast);
                    return -1;
                }
            }
            memcpy(*output + *output_pos, evaluator->output_buffer, evaluator->output_size);
            *output_pos += evaluator->output_size;
        }
        
        ast_evaluator_free(evaluator);
        ast_free(ast);
        return 0;
    }
    
    // Handle control flow directives
    if (strncmp(content, "if ", 3) == 0) {
        const char* condition = content + 3;
        while (*condition == ' ' || *condition == '\t') condition++;
        
        bool result = ast_evaluate_condition(condition, ctx->variables);
        
        // Push to if stack
        if (ctx->if_stack_size < MAX_IF_DEPTH) {
            ctx->if_stack[ctx->if_stack_size].condition_met = result;
            ctx->if_stack[ctx->if_stack_size].branch_executed = result;
            ctx->if_stack[ctx->if_stack_size].in_elif = false;
            ctx->if_stack_size++;
        }
        return 0;
    }
    else if (strncmp(content, "elif ", 5) == 0) {
        if (ctx->if_stack_size > 0) {
            if_stack_entry* current = &ctx->if_stack[ctx->if_stack_size - 1];
            
            if (!current->branch_executed) {
                const char* condition = content + 5;
                while (*condition == ' ' || *condition == '\t') condition++;
                
                bool result = ast_evaluate_condition(condition, ctx->variables);
                current->condition_met = result;
                if (result) {
                    current->branch_executed = true;
                }
            } else {
                current->condition_met = false;
            }
            current->in_elif = true;
        }
        return 0;
    }
    else if (strcmp(content, "else") == 0) {
        if (ctx->if_stack_size > 0) {
            if_stack_entry* current = &ctx->if_stack[ctx->if_stack_size - 1];
            current->condition_met = !current->branch_executed;
            current->in_elif = false;
        }
        return 0;
    }
    else if (strcmp(content, "endif") == 0) {
        if (ctx->if_stack_size > 0) {
            ctx->if_stack_size--;
        }
        return 0;
    }
    else if (strncmp(content, "for ", 4) == 0) {
        // For loops are handled differently - they don't produce output here
        // The main processor will handle loop iteration
        return 0;
    }
    else if (strcmp(content, "endfor") == 0) {
        // End of for loop marker
        return 0;
    }
    
    // For other directives, try AST parsing
    token* tokens = lexer_enhanced_tokenize(content, "xmd_directive");
    if (!tokens) {
        return -1;
    }
    
    // Parse the tokens into AST
    ast_node* ast = ast_parse_program(tokens);
    token_list_free(tokens);
    
    if (!ast) {
        return -1;
    }
    
    // Create evaluator
    ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
    if (!evaluator) {
        ast_free(ast);
        return -1;
    }
    
    // Debug removed - no longer needed
    
    // Process each statement in the directive
    for (size_t i = 0; i < ast->data.program.statement_count; i++) {
        ast_node* stmt = ast->data.program.statements[i];
        
        if (stmt->type == AST_ASSIGNMENT) {
            // Handle assignments
            ast_evaluate_assignment(stmt, evaluator);
        } else {
            // Evaluate other expressions (might generate output)
            // Set statement context flag
            evaluator->in_statement_context = true;
            ast_value* result = ast_evaluate(stmt, evaluator);
            evaluator->in_statement_context = false;
            
            if (result) {
                ast_value_free(result);
            }
        }
    }
    
    // Get any output generated by the evaluator
    if (evaluator->output_buffer && evaluator->output_size > 0) {
        size_t required = *output_pos + evaluator->output_size;
        if (required >= *output_capacity) {
            *output_capacity = required * 2;
            *output = realloc(*output, *output_capacity);
            if (!*output) {
                ast_evaluator_free(evaluator);
                ast_free(ast);
                return -1;
            }
        }
        memcpy(*output + *output_pos, evaluator->output_buffer, evaluator->output_size);
        *output_pos += evaluator->output_size;
    }
    
    ast_evaluator_free(evaluator);
    ast_free(ast);
    return 0;
}

/**
 * @brief Find matching endfor directive
 * @param input Input string starting after the for directive
 * @return Pointer to the endfor directive or NULL if not found
 */
static const char* ast_find_matching_endfor(const char* input) {
    int depth = 1;
    const char* ptr = input;
    
    while (*ptr && depth > 0) {
        const char* comment_start = strstr(ptr, "<!--");
        if (!comment_start) break;
        
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) break;
        
        const char* xmd_start = comment_start + 4;
        while (*xmd_start == ' ' || *xmd_start == '\t' || *xmd_start == '\n') xmd_start++;
        
        if (strncmp(xmd_start, "xmd:", 4) == 0) {
            const char* directive = xmd_start + 4;
            while (*directive == ' ' || *directive == '\t') directive++;
            
            if (strncmp(directive, "for ", 4) == 0) {
                depth++;
            } else if (strncmp(directive, "endfor", 6) == 0) {
                depth--;
                if (depth == 0) {
                    return comment_start;
                }
            }
        }
        
        ptr = comment_end + 3;
    }
    
    return NULL;
}

/**
 * @brief Process XMD content using AST parser
 * @param input Input content containing XMD directives
 * @param variables Variable store
 * @return Processed content (caller must free) or NULL on error
 */
char* ast_process_xmd_content(const char* input, store* variables) {
    if (!input || !variables) {
        return NULL;
    }
    
    // Create processor context
    processor_context* ctx = create_context(variables);
    if (!ctx) {
        return NULL;
    }
    
    // Set the source file path if available from global context
    const char* current_file = xmd_get_current_file_path();
    if (current_file) {
        set_context_source_file(ctx, current_file);
    }
    
    size_t input_len = strlen(input);
    size_t output_capacity = input_len * 2 + 1;
    char* output = malloc(output_capacity);
    if (!output) {
        destroy_context(ctx);
        return NULL;
    }
    
    size_t output_pos = 0;
    const char* ptr = input;
    
    while (*ptr) {
        // Look for HTML comment start
        const char* comment_start = strstr(ptr, "<!--");
        
        if (!comment_start) {
            // No more comments, copy rest if executing
            if (should_execute_block(ctx)) {
                size_t remaining = strlen(ptr);
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                    if (!output) {
                        destroy_context(ctx);
                        return NULL;
                    }
                }
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before comment if executing
        if (should_execute_block(ctx)) {
            size_t before_len = comment_start - ptr;
            if (output_pos + before_len >= output_capacity) {
                output_capacity = (output_pos + before_len + 1) * 2;
                output = realloc(output, output_capacity);
                if (!output) {
                    destroy_context(ctx);
                    return NULL;
                }
            }
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find comment end
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) {
            // Malformed comment, copy and break
            if (should_execute_block(ctx)) {
                size_t remaining = strlen(comment_start);
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Check if it's an XMD directive
        const char* xmd_start = comment_start + 4;
        while (*xmd_start == ' ' || *xmd_start == '\t' || *xmd_start == '\n') xmd_start++;
        
        if (strncmp(xmd_start, "xmd:", 4) == 0) {
            const char* directive_start = xmd_start + 4;
            while (*directive_start == ' ' || *directive_start == '\t') directive_start++;
            
            // Check if it's a for loop
            if (strncmp(directive_start, "for ", 4) == 0 && should_execute_block(ctx)) {
                // Parse for loop arguments
                const char* args = directive_start + 4;
                while (*args == ' ' || *args == '\t') args++;
                
                // Extract loop arguments
                size_t args_len = comment_end - args;
                char* args_str = malloc(args_len + 1);
                if (!args_str) {
                    ptr = comment_end + 3;
                    continue;
                }
                memcpy(args_str, args, args_len);
                args_str[args_len] = '\0';
                
                // Parse "item in collection" syntax
                char* in_pos = strstr(args_str, " in ");
                if (in_pos) {
                    *in_pos = '\0';
                    char* var_name = trim_whitespace(args_str);
                    char* collection_expr = trim_whitespace(in_pos + 4);
                    
                    // Get the collection
                    variable* collection = store_get(ctx->variables, collection_expr);
                    
                    // Find the matching endfor
                    const char* endfor_start = ast_find_matching_endfor(comment_end + 3);
                    if (endfor_start && collection && collection->type == VAR_ARRAY) {
                        // Extract loop body
                        const char* body_start = comment_end + 3;
                        size_t body_len = endfor_start - body_start;
                        char* loop_body = malloc(body_len + 1);
                        if (loop_body) {
                            memcpy(loop_body, body_start, body_len);
                            loop_body[body_len] = '\0';
                            
                            // Iterate over array elements
                            size_t array_size = collection->value.array_value->count;
                            for (size_t i = 0; i < array_size; i++) {
                                variable* item = collection->value.array_value->items[i];
                                if (item) {
                                    // Create a copy of the item for the loop variable
                                    variable* loop_var = variable_copy(item);
                                    if (loop_var) {
                                        // Set loop variable
                                        store_set(ctx->variables, var_name, loop_var);
                                        variable_unref(loop_var);
                                    }
                                    
                                    // Process loop body recursively
                                    char* iteration_result = ast_process_xmd_content(loop_body, ctx->variables);
                                    if (iteration_result) {
                                        size_t result_len = strlen(iteration_result);
                                        if (output_pos + result_len >= output_capacity) {
                                            output_capacity = (output_pos + result_len + 1) * 2;
                                            output = realloc(output, output_capacity);
                                            if (!output) {
                                                free(iteration_result);
                                                free(loop_body);
                                                free(args_str);
                                                destroy_context(ctx);
                                                return NULL;
                                            }
                                        }
                                        memcpy(output + output_pos, iteration_result, result_len);
                                        output_pos += result_len;
                                        free(iteration_result);
                                    }
                                }
                            }
                            
                            free(loop_body);
                        }
                        
                        // Skip to after endfor
                        const char* endfor_end = strstr(endfor_start + 4, "-->");
                        if (endfor_end) {
                            ptr = endfor_end + 3;
                        } else {
                            ptr = endfor_start + strlen(endfor_start);
                        }
                        free(args_str);
                        continue;
                    }
                }
                
                free(args_str);
            }
            
            // Extract directive content for other directives
            if (!strncmp(directive_start, "for ", 4)) {
                // Skip - already handled above
            } else if (should_execute_block(ctx)) {
                size_t directive_len = comment_end - xmd_start;
                char* directive = malloc(directive_len + 1);
                if (directive) {
                    memcpy(directive, xmd_start, directive_len);
                    directive[directive_len] = '\0';
                    
                    // Process the directive (debug removed)
                    
                    // Process the directive
                    ast_process_directive_content(directive, ctx, &output, &output_capacity, &output_pos);
                    free(directive);
                }
            }
        } else {
            // Not an XMD comment, copy if executing
            if (should_execute_block(ctx)) {
                size_t comment_len = (comment_end + 3) - comment_start;
                if (output_pos + comment_len >= output_capacity) {
                    output_capacity = (output_pos + comment_len + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, comment_len);
                output_pos += comment_len;
            }
        }
        
        ptr = comment_end + 3;
    }
    
    output[output_pos] = '\0';
    
    // Perform variable substitution on the entire output
    char* substituted = ast_substitute_variables(output, variables);
    free(output);
    
    destroy_context(ctx);
    return substituted ? substituted : strdup("");
}