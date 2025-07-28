/**
 * @file ast_value_free.c
 * @brief Free AST value
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Free AST value
 * @param value Value to free
 */
void ast_value_free(ast_value* value) {
    if (!value) {
        return;
    }
    
    if (value->type == AST_VAL_STRING) {
        free(value->value.string_value);
    }
    
    free(value);
}