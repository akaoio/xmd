/**
 * @file parser_peek_token.c
 * @brief Peek at next token without advancing
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/ast_parser.h"

/**
 * @brief Peek at next token without advancing parser
 * @param state Parser state
 * @return Next token or NULL if at end
 */
token* parser_peek_token(parser_state* state) {
    if (!state || !state->current) return NULL;
    return state->current->next;
}