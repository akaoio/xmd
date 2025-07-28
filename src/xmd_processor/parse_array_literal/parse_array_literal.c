/**
 * @file parse_array_literal.c
 * @brief Parse array literal syntax implementation (now uses AST)
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Parse array literal from string (now uses AST parser)
 * @param input Input string containing array literal like ["item1", "item2"]
 * @return Array variable or NULL on error
 */
variable* parse_array_literal(const char* input) {
    return ast_parse_array_literal(input);
}