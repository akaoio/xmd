/**
 * @file parser_state_create.c
 * @brief Create new parser state
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/ast_parser.h"
#include "../../../../include/utils.h"
#include "../../../../src/utils/common/common_macros.h"

/**
 * @brief Create new parser state
 * @param tokens Token list to parse
 * @param filename Source filename for error reporting
 * @return New parser state or NULL on error
 */
parser_state* parser_state_create(token* tokens, const char* filename) {
    XMD_VALIDATE_PTRS(NULL, tokens);
    
    XMD_MALLOC_SAFE(parser_state, state);
    
    state->tokens = tokens;
    state->current = tokens;
    state->position = 0;
    state->has_error = false;
    state->error_message = NULL;
    state->filename = filename ? xmd_strdup(filename) : NULL;
    
    return state;
}