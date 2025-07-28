/**
 * @file parser_has_error.c
 * @brief Check if parser has encountered an error
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../include/ast_parser.h"

// Global error state for simple error checking
bool global_parser_error = false;
char* global_error_message = NULL;

/**
 * @brief Check if parser has encountered an error
 * @return true if error occurred, false otherwise
 */
bool parser_has_error(void) {
    return global_parser_error;
}