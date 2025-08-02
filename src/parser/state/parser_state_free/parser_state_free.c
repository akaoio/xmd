/**
 * @file parser_state_free.c
 * @brief Free parser state memory
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "../../../../include/ast_parser.h"
#include "../../../../include/utils.h"

/**
 * @brief Free parser state and associated memory
 * @param state Parser state to free
 */
void parser_state_free(parser_state* state) {
    if (!state) return;
    
    if (state->error_message) {
        free(state->error_message);
    }
    if (state->filename) {
        free(state->filename);
    }
    
    free(state);
}