/**
 * @file parser_advance_token.c
 * @brief Advance parser to next token
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/ast_parser.h"

/**
 * @brief Advance parser to next token
 * @param state Parser state
 * @return Current token after advancing
 */
token* parser_advance_token(parser_state* state) {
    if (!state || !state->current) return NULL;
    
    if (state->current->next) {
        state->current = state->current->next;
        state->position++;
    }
    
    return state->current;
}