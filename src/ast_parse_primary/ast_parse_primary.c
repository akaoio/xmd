/**
 * @file ast_parse_primary.c
 * @brief Parse primary expression (literals, identifiers, parentheses)
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
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
            } else {
                ast_node* node = ast_create_variable_ref(tok->value, loc);
                parser_advance_token(state);
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