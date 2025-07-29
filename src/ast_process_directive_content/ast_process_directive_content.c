/**
 * @file ast_process_directive_content.c
 * @brief Process XMD directive content using AST
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
#include "../../include/ast_process_directive_content.h"

/**
 * @brief Process XMD directive found in HTML comment
 * @param directive_content Content between <!-- xmd: and -->
 * @param ctx Processor context
 * @param output Output buffer for generated content
 * @param output_capacity Current capacity of output buffer
 * @param output_pos Current position in output buffer
 * @return 0 on success, -1 on error
 */
int ast_process_directive_content(const char* directive_content, 
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
    
    // Handle control flow directives - rest of function continues in original file
    return -1; // Temporary - will be handled by main processor
}