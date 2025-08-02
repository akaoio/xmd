/**
 * @file parser_set_error.c
 * @brief Set parser error message
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/ast_parser.h"
#include "../../../../include/utils.h"

/**
 * @brief Set error message in parser state
 * @param state Parser state
 * @param message Error message format string
 * @param ... Format arguments
 */
void parser_set_error(parser_state* state, const char* message, ...) {
    if (!state || !message) return;
    
    // Free existing error message
    if (state->error_message) {
        free(state->error_message);
    }
    
    // Allocate new error message
    state->error_message = xmd_malloc(512);
    if (!state->error_message) {
        state->has_error = true;
        return;
    }
    
    // Format error message
    va_list args;
    va_start(args, message);
    vsnprintf(state->error_message, 512, message, args);
    va_end(args);
    
    state->has_error = true;
}