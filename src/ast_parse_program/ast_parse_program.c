/**
 * @file ast_parse_program.c
 * @brief Parse program from token stream
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Parse program from token stream
 * @param tokens Token stream from lexer
 * @return AST program node or NULL on error
 */
ast_node* ast_parse_program(token* tokens) {
    if (!tokens) {
        return NULL;
    }
    
    parser_state* state = parser_state_create(tokens, "input");
    if (!state) {
        return NULL;
    }
    
    ast_node* program = ast_create_program();
    if (!program) {
        parser_state_free(state);
        return NULL;
    }
    
    // Parse statements until EOF
    while (state->current_token && state->current_token->type != TOKEN_EOF) {
        ast_node* stmt = ast_parse_statement(state);
        if (stmt) {
            if (ast_add_statement(program, stmt) != 0) {
                ast_free(stmt);
                break;
            }
        } else if (state->has_error) {
            break;
        } else {
            // Skip unknown token
            parser_advance_token(state);
        }
    }
    
    bool had_error = state->has_error;
    parser_state_free(state);
    
    if (had_error) {
        ast_free(program);
        return NULL;
    }
    
    return program;
}