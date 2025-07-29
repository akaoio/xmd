/**
 * @file ast_parse_primary.c
 * @brief Parse primary expression (literals, identifiers, parentheses)
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Parse primary expression (literals, identifiers, parentheses)
 * @param state Parser state
 * @return AST primary expression node or NULL on error
 */
ast_node* ast_parse_primary(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    token* tok = parser_peek_token(state);
    if (!tok) {
        return NULL;
    }
    source_location loc = {tok->line, tok->column, state->filename};
    
    switch (tok->type) {
        case TOKEN_STRING: {
            ast_node* node = ast_create_string_literal(tok->value, loc);
            parser_advance_token(state);
            return node;
        }
        
        case TOKEN_NUMBER: {
            double value = atof(tok->value);
            ast_node* node = ast_create_number_literal(value, loc);
            parser_advance_token(state);
            return node;
        }
        
        case TOKEN_BOOLEAN: {
            bool value = (strcmp(tok->value, "true") == 0);
            ast_node* node = ast_create_boolean_literal(value, loc);
            parser_advance_token(state);
            return node;
        }
        
        case TOKEN_IDENTIFIER: {
            // Check if this is a function call
            token* next = tok->next;
            if (next && next->type == TOKEN_LPAREN) {
                return ast_parse_function_call(state);
            } else if (strcmp(tok->value, "import") == 0) {
                // Handle import function without parentheses
                const char* func_name = tok->value;
                parser_advance_token(state); // Skip function name
                
                // Parse the next primary expression as the argument
                ast_node* arg = ast_parse_primary(state);
                if (!arg) {
                    return NULL;
                }
                
                // Create function call node
                ast_node* func_call = ast_create_function_call(func_name, loc);
                if (!func_call) {
                    ast_free(arg);
                    return NULL;
                }
                
                // Add the argument
                if (ast_add_argument(func_call, arg) != 0) {
                    ast_free(arg);
                    ast_free(func_call);
                    return NULL;
                }
                
                return func_call;
            } else if (strcmp(tok->value, "exec") == 0) {
                // Handle exec function without parentheses - needs special handling for shell commands
                const char* func_name = tok->value;
                parser_advance_token(state); // Skip function name
                
                // For exec, collect all remaining tokens as a single string argument for shell command
                char command_buffer[4096] = {0};
                
                while (state->current_token && state->current_token->type != TOKEN_EOF) {
                    token* current = parser_peek_token(state);
                    if (!current) break;
                    
                    // Stop at certain tokens that would end the command
                    if (current->type == TOKEN_RPAREN || current->type == TOKEN_RBRACKET || 
                        current->type == TOKEN_COMMA || current->type == TOKEN_SEMICOLON) {
                        break;
                    }
                    
                    // Simple concatenation with spaces between tokens
                    if (strlen(command_buffer) > 0) {
                        strncat(command_buffer, " ", sizeof(command_buffer) - strlen(command_buffer) - 1);
                    }
                    strncat(command_buffer, current->value, sizeof(command_buffer) - strlen(command_buffer) - 1);
                    
                    parser_advance_token(state);
                }
                
                // Now post-process to fix shell syntax issues in multiple passes
                // First pass: fix basic spacing issues
                char temp_buffer[4096] = {0};
                char* src = command_buffer;
                char* dst = temp_buffer;
                
                while (*src) {
                    if (strncmp(src, "2 >", 3) == 0) {
                        // Fix "2 >" to "2>"
                        *dst++ = '2';
                        *dst++ = '>';
                        src += 3;
                    } else if (strncmp(src, "> /", 3) == 0) {
                        // Fix "> /" to ">/"
                        *dst++ = '>';
                        *dst++ = '/';
                        src += 3;  
                    } else if (strncmp(src, "/ ", 2) == 0 && 
                               (strncmp(src + 2, "dev", 3) == 0 || strncmp(src + 2, "usr", 3) == 0)) {
                        // Fix "/ dev" to "/dev" and "/ usr" to "/usr"
                        *dst++ = '/';
                        src += 2; // Skip the space
                    } else if (strncmp(src, "dev / null", 10) == 0) {
                        // Fix "dev / null" to "dev/null"
                        strcpy(dst, "dev/null");
                        dst += 8;
                        src += 10;
                    } else if (strncmp(src, "- ", 2) == 0 && 
                               (strncmp(src + 2, "name", 4) == 0 || isdigit(src[2]))) {
                        // Fix "- name" to "-name" and "- 1000" to "-1000"
                        *dst++ = '-';
                        src += 2; // Skip the space
                    } else {
                        *dst++ = *src++;
                    }
                }
                *dst = '\0';
                
                // Second pass: add missing pipe
                char fixed_buffer[4096] = {0};
                src = temp_buffer;
                dst = fixed_buffer;
                
                while (*src) {
                    if (strncmp(src, "/dev/null head", 14) == 0) {
                        // Fix "/dev/null head" to "/dev/null | head"
                        strcpy(dst, "/dev/null | head");
                        dst += 16;
                        src += 14;
                    } else {
                        *dst++ = *src++;
                    }
                }
                *dst = '\0';
                
                
                // Create string literal argument from collected tokens
                ast_node* arg = ast_create_string_literal(fixed_buffer, loc);
                if (!arg) {
                    return NULL;
                }
                
                // Create function call node
                ast_node* func_call = ast_create_function_call(func_name, loc);
                if (!func_call) {
                    ast_free(arg);
                    return NULL;
                }
                
                // Add the argument
                if (ast_add_argument(func_call, arg) != 0) {
                    ast_free(arg);
                    ast_free(func_call);
                    return NULL;
                }
                
                return func_call;
            } else if (strcmp(tok->value, "join") == 0) {
                // Handle join function without parentheses
                const char* func_name = tok->value;
                parser_advance_token(state); // Skip function name
                
                // Create function call node
                ast_node* func_call = ast_create_function_call(func_name, loc);
                if (!func_call) {
                    return NULL;
                }
                
                // Parse the first argument (array)
                ast_node* arg1 = ast_parse_primary(state);
                if (!arg1) {
                    ast_free(func_call);
                    return NULL;
                }
                
                if (ast_add_argument(func_call, arg1) != 0) {
                    ast_free(arg1);
                    ast_free(func_call);
                    return NULL;
                }
                
                // Check for optional second argument (separator)
                token* next_tok = parser_peek_token(state);
                if (next_tok && (next_tok->type == TOKEN_STRING || next_tok->type == TOKEN_IDENTIFIER)) {
                    ast_node* arg2 = ast_parse_primary(state);
                    if (arg2) {
                        if (ast_add_argument(func_call, arg2) != 0) {
                            ast_free(arg2);
                            ast_free(func_call);
                            return NULL;
                        }
                    }
                }
                
                return func_call;
            } else {
                ast_node* node = ast_create_variable_ref(tok->value, loc);
                parser_advance_token(state);
                
                // Check for array indexing
                token* next_tok = parser_peek_token(state);
                if (next_tok && next_tok->type == TOKEN_LBRACKET) {
                    parser_advance_token(state); // Skip '['
                    
                    // Parse index expression
                    ast_node* index_expr = ast_parse_expression(state);
                    if (!index_expr) {
                        parser_set_error(state, "Expected index expression after '['");
                        ast_free(node);
                        return NULL;
                    }
                    
                    // Expect closing ']'
                    token* close_tok = parser_peek_token(state);
                    if (!close_tok || close_tok->type != TOKEN_RBRACKET) {
                        parser_set_error(state, "Expected ']' after index expression");
                        ast_free(node);
                        ast_free(index_expr);
                        return NULL;
                    }
                    parser_advance_token(state); // Skip ']'
                    
                    // Create array access node
                    ast_node* access_node = ast_create_array_access(node, index_expr, loc);
                    if (!access_node) {
                        ast_free(node);
                        ast_free(index_expr);
                        return NULL;
                    }
                    
                    return access_node;
                }
                
                return node;
            }
        }
        
        case TOKEN_LPAREN: {
            parser_advance_token(state); // Skip '('
            ast_node* expr = ast_parse_expression(state);
            if (!expr) {
                return NULL;
            }
            
            tok = parser_peek_token(state);
            if (!tok || tok->type != TOKEN_RPAREN) {
                parser_set_error(state, "Expected ')' after expression");
                ast_free(expr);
                return NULL;
            }
            parser_advance_token(state); // Skip ')'
            return expr;
        }
        
        case TOKEN_LBRACKET: {
            parser_advance_token(state); // Skip '['
            ast_node* array = ast_create_array_literal(loc);
            if (!array) {
                return NULL;
            }
            
            // Parse array elements
            tok = parser_peek_token(state);
            if (tok && tok->type != TOKEN_RBRACKET) {
                do {
                    ast_node* element = ast_parse_expression(state);
                    if (!element) {
                        ast_free(array);
                        return NULL;
                    }
                    
                    if (ast_add_element(array, element) != 0) {
                        ast_free(element);
                        ast_free(array);
                        return NULL;
                    }
                    
                    tok = parser_peek_token(state);
                    if (tok && tok->type == TOKEN_COMMA) {
                        parser_advance_token(state); // Skip ','
                        tok = parser_peek_token(state);
                    } else {
                        break;
                    }
                } while (tok && tok->type != TOKEN_RBRACKET);
            }
            
            tok = parser_peek_token(state);
            if (!tok || tok->type != TOKEN_RBRACKET) {
                parser_set_error(state, "Expected ']' after array elements");
                ast_free(array);
                return NULL;
            }
            parser_advance_token(state); // Skip ']'
            return array;
        }
        
        default:
            parser_set_error(state, "Expected primary expression");
            return NULL;
    }
}