/**
 * @file parser_state_create.c
 * @brief Create parser state from token stream
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_parser.h"

/**
 * @brief Create parser state from token stream
 * @param tokens Token stream
 * @param filename Source filename
 * @return Parser state or NULL on error
 */
parser_state* parser_state_create(token* tokens, const char* filename) {
    if (!tokens) {
        return NULL;
    }
    
    parser_state* state = malloc(sizeof(parser_state));
    if (!state) {
        return NULL;
    }
    
    state->tokens = tokens;
    state->current_token = tokens;
    state->position = 0;
    state->filename = filename ? strdup(filename) : NULL;
    state->has_error = false;
    state->error_message = NULL;
    
    return state;
}