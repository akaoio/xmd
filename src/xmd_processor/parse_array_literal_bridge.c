/**
 * @file parse_array_literal_bridge.c
 * @brief Bridge from parse_array_literal to ast_parse_array_literal
 * @author XMD Team
 * @date 2025-07-29
 */

#include "../../include/variable.h"

// External AST function
extern variable* ast_parse_array_literal(const char* input);

/**
 * @brief Bridge function that delegates to AST implementation
 * @param input Array literal string
 * @return Array variable or NULL on error
 */
variable* parse_array_literal(const char* input) {
    return ast_parse_array_literal(input);
}