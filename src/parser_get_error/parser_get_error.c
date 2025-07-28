/**
 * @file parser_get_error.c
 * @brief Get last parser error message
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../include/ast_parser.h"

// External reference to global error message
extern char* global_error_message;

/**
 * @brief Get last parser error message
 * @return Error message string or NULL
 */
const char* parser_get_error(void) {
    return global_error_message;
}