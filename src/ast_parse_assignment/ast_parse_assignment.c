/**
 * @file ast_parse_assignment.c
 * @brief Parse assignment statement
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Parse assignment statement
 * @param state Parser state
 * @return AST assignment node or NULL on error
 */
ast_node* ast_parse_assignment(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    token* var_tok = parser_peek_token(state);
    if (!var_tok || var_tok->type != TOKEN_IDENTIFIER) {
        parser_set_error(state, "Expected variable name in assignment");
        return NULL;
    }
    
    source_location loc = {var_tok->line, var_tok->column, state->filename};
    char* var_name = var_tok->value;
    parser_advance_token(state); // Skip variable name
    
    token* op_tok = parser_peek_token(state);
    if (!op_tok || op_tok->type != TOKEN_OPERATOR) {
        parser_set_error(state, "Expected assignment operator");
        return NULL;
    }
    
    binary_operator op;
    if (strcmp(op_tok->value, "=") == 0) {
        op = BINOP_ASSIGN;
    } else if (strcmp(op_tok->value, "+=") == 0) {
        op = BINOP_ASSIGN_ADD;
    } else {
        parser_set_error(state, "Expected '=' or '+=' in assignment");
        return NULL;
    }
    
    parser_advance_token(state); // Skip assignment operator
    
    ast_node* value = ast_parse_expression(state);
    if (!value) {
        return NULL;
    }
    
    ast_node* assignment = ast_create_assignment(var_name, op, value, loc);
    if (!assignment) {
        ast_free(value);
        return NULL;
    }
    
    return assignment;
}