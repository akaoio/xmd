/**
 * @file parser_has_error.c
 * @brief Check if parser has error
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/ast_parser.h"

/**
 * @brief Check if parser state has error
 * @param state Parser state
 * @return true if error exists, false otherwise
 */
bool parser_has_error(parser_state* state) {
    return state ? state->has_error : true;
}