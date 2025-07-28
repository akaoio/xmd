/**
 * @file parser_advance_token.c
 * @brief Advance parser to next token
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../include/ast_parser.h"

/**
 * @brief Advance to next token
 * @param state Parser state
 * @return Current token after advance
 */
token* parser_advance_token(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    if (state->current_token->next) {
        state->current_token = state->current_token->next;
        state->position++;
    }
    
    return state->current_token;
}