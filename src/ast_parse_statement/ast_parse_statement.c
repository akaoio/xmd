/**
 * @file ast_parse_statement.c
 * @brief Parse single statement
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Parse single statement
 * @param state Parser state
 * @return AST statement node or NULL on error
 */
ast_node* ast_parse_statement(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    token* tok = parser_peek_token(state);
    if (!tok || tok->type == TOKEN_EOF) {
        return NULL;
    }
    
    // Check if this is an assignment (identifier followed by = or +=)
    if (tok->type == TOKEN_IDENTIFIER && tok->next) {
        token* next = tok->next;
        if (next->type == TOKEN_OPERATOR && 
            (strcmp(next->value, "=") == 0 || strcmp(next->value, "+=") == 0)) {
            return ast_parse_assignment(state);
        }
    }
    
    // Otherwise, parse as expression statement
    return ast_parse_expression(state);
}