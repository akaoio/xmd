/**
 * @file parser_set_error.c
 * @brief Set parser error with message
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_parser.h"

// External references to global error state
extern bool global_parser_error;
extern char* global_error_message;

/**
 * @brief Set parser error with message
 * @param state Parser state
 * @param message Error message
 */
void parser_set_error(parser_state* state, const char* message) {
    global_parser_error = true;
    
    if (state) {
        state->has_error = true;
        free(state->error_message);
        state->error_message = message ? strdup(message) : NULL;
    }
    
    free(global_error_message);
    global_error_message = message ? strdup(message) : NULL;
}