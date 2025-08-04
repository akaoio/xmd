/**
 * @file parser_advance_token.c
 * @brief Implementation of parser_advance_token function
 * 
 * This file contains ONLY the parser_advance_token function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include "ast_parser.h"
#include "token.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Advance to next token in parser state
 * @param state Parser state
 * @return Current token after advance or NULL
 */
token* parser_advance_token(parser_state* state) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, state);
    
    if (state->current_token && state->current_token->next) {
        state->current_token = state->current_token->next;
    }
    
    return state->current_token;
}