/**
 * @file parser_state_free.c
 * @brief Free parser state
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_parser.h"

/**
 * @brief Free parser state
 * @param state Parser state to free
 */
void parser_state_free(parser_state* state) {
    if (!state) {
        return;
    }
    
    free((char*)state->filename);
    free(state->error_message);
    free(state);
}