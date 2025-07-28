/**
 * @file ast_parse_function_call.c
 * @brief Parse function call
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Parse function call
 * @param state Parser state
 * @return AST function call node or NULL on error
 */
ast_node* ast_parse_function_call(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    token* name_tok = parser_peek_token(state);
    if (!name_tok || name_tok->type != TOKEN_IDENTIFIER) {
        parser_set_error(state, "Expected function name");
        return NULL;
    }
    
    source_location loc = {name_tok->line, name_tok->column, state->filename};
    ast_node* func_call = ast_create_function_call(name_tok->value, loc);
    if (!func_call) {
        return NULL;
    }
    
    parser_advance_token(state); // Skip function name
    
    token* lparen = parser_peek_token(state);
    if (!lparen || lparen->type != TOKEN_LPAREN) {
        parser_set_error(state, "Expected '(' after function name");
        ast_free(func_call);
        return NULL;
    }
    parser_advance_token(state); // Skip '('
    
    // Parse arguments
    token* tok = parser_peek_token(state);
    if (tok && tok->type != TOKEN_RPAREN) {
        while (true) {
            ast_node* arg = ast_parse_expression(state);
            if (!arg) {
                ast_free(func_call);
                return NULL;
            }
            
            if (ast_add_argument(func_call, arg) != 0) {
                ast_free(arg);
                ast_free(func_call);
                return NULL;
            }
            
            tok = parser_peek_token(state);
            if (!tok) {
                parser_set_error(state, "Unexpected end of input in function call");
                ast_free(func_call);
                return NULL;
            }
            
            if (tok->type == TOKEN_COMMA) {
                parser_advance_token(state); // Skip ','
                continue;
            } else if (tok->type == TOKEN_RPAREN) {
                break;
            } else {
                parser_set_error(state, "Expected ',' or ')' in function call");
                ast_free(func_call);
                return NULL;
            }
        }
    }
    
    token* rparen = parser_peek_token(state);
    if (!rparen || rparen->type != TOKEN_RPAREN) {
        parser_set_error(state, "Expected ')' after function arguments");
        ast_free(func_call);
        return NULL;
    }
    parser_advance_token(state); // Skip ')'
    
    return func_call;
}