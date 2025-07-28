/**
 * @file ast_substitute_variables.c
 * @brief AST-based variable substitution implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/xmd_processor_internal.h"

/**
 * @brief Substitute {{variable}} patterns using AST (replaces string-based substitute_variables)
 * @param text Input text containing {{variable}} patterns
 * @param variables Variable store for variable lookups
 * @return New string with variables substituted (caller must free) or NULL on error
 */
char* ast_substitute_variables(const char* text, store* variables) {
    if (!text) {
        return NULL;
    }
    
    size_t text_len = strlen(text);
    size_t output_capacity = text_len * 2;
    char* output = malloc(output_capacity);
    if (!output) {
        return NULL;
    }
    size_t output_pos = 0;
    
    const char* ptr = text;
    while (*ptr) {
        // Look for variable substitution patterns {{...}}
        if (ptr[0] == '{' && ptr[1] == '{') {
            const char* close = strstr(ptr + 2, "}}");
            if (close) {
                // Extract variable expression
                size_t expr_len = close - ptr - 2;
                char* expr = malloc(expr_len + 1);
                if (!expr) {
                    free(output);
                    return NULL;
                }
                strncpy(expr, ptr + 2, expr_len);
                expr[expr_len] = '\0';
                
                // Trim whitespace
                char* trimmed_expr = trim_whitespace(expr);
                
                // Use AST to evaluate the variable expression
                // For simple variables, just do direct lookup
                // For complex expressions, use AST evaluation
                char* var_value = NULL;
                
                if (strchr(trimmed_expr, '+') || strchr(trimmed_expr, '-') || 
                    strchr(trimmed_expr, '*') || strchr(trimmed_expr, '/') ||
                    strchr(trimmed_expr, '(') || strchr(trimmed_expr, ')')) {
                    // Complex expression - use AST evaluation
                    token* tokens = lexer_enhanced_tokenize(trimmed_expr, "variable_expr");
                    if (tokens) {
                        ast_node* ast = ast_parse_program(tokens);
                        token_list_free(tokens);
                        
                        if (ast && ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
                            // Create temporary processor context
                            processor_context temp_ctx = {0};
                            temp_ctx.variables = variables;
                            
                            ast_evaluator* evaluator = ast_evaluator_create(variables, &temp_ctx);
                            if (evaluator) {
                                ast_node* expr_node = ast->data.program.statements[0];
                                ast_value* result = ast_evaluate(expr_node, evaluator);
                                
                                if (result) {
                                    switch (result->type) {
                                        case AST_VAL_STRING:
                                            if (result->value.string_value) {
                                                var_value = strdup(result->value.string_value);
                                            }
                                            break;
                                        case AST_VAL_NUMBER: {
                                            var_value = malloc(64);
                                            if (var_value) {
                                                snprintf(var_value, 64, "%.15g", result->value.number_value);
                                            }
                                            break;
                                        }
                                        case AST_VAL_BOOLEAN:
                                            var_value = strdup(result->value.boolean_value ? "true" : "false");
                                            break;
                                        default:
                                            var_value = strdup("");
                                            break;
                                    }
                                    ast_value_free(result);
                                }
                                ast_evaluator_free(evaluator);
                            }
                            ast_free(ast);
                        }
                    }
                } else {
                    // Simple variable lookup
                    variable* var = store_get(variables, trimmed_expr);
                    if (var) {
                        var_value = variable_to_string(var);
                    } else {
                        var_value = strdup("");
                    }
                }
                
                if (!var_value) {
                    var_value = strdup("");
                }
                
                // Ensure output buffer has enough space
                size_t value_len = strlen(var_value);
                if (output_pos + value_len >= output_capacity) {
                    output_capacity = (output_pos + value_len + 1000) * 2;
                    char* new_output = realloc(output, output_capacity);
                    if (!new_output) {
                        free(output);
                        free(var_value);
                        free(expr);
                        return NULL;
                    }
                    output = new_output;
                }
                
                // Copy variable value to output
                memcpy(output + output_pos, var_value, value_len);
                output_pos += value_len;
                
                free(var_value);
                free(expr);
                ptr = close + 2;
                continue;
            }
        }
        
        // Regular character - ensure buffer space
        if (output_pos >= output_capacity - 1) {
            output_capacity *= 2;
            char* new_output = realloc(output, output_capacity);
            if (!new_output) {
                free(output);
                return NULL;
            }
            output = new_output;
        }
        
        output[output_pos++] = *ptr++;
    }
    
    output[output_pos] = '\0';
    return output;
}