/**
 * @file parser_peek_token.c
 * @brief Peek at current token without advancing
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../include/ast_parser.h"

/**
 * @brief Peek at current token without advancing
 * @param state Parser state
 * @return Current token
 */
token* parser_peek_token(parser_state* state) {
    if (!state) {
        return NULL;
    }
    
    return state->current_token;
}