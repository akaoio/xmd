/**
 * @file parser_get_error.c
 * @brief Get parser error message
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/ast_parser.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Get current error message from parser state
 * @param state Parser state
 * @return Error message string or NULL if no error
 */
const char* parser_get_error(parser_state* state) {
    XMD_VALIDATE_PTRS(NULL, state);
    if (!state->has_error) return NULL;
    return state->error_message;
}