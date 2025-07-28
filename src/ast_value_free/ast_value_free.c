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
    } else if (value->type == AST_VAL_ARRAY) {
        if (value->value.array_value.elements) {
            for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                ast_value_free(value->value.array_value.elements[i]);
            }
            free(value->value.array_value.elements);
        }
    }
    
    free(value);
}