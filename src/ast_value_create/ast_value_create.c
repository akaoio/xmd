/**
 * @file ast_value_create.c
 * @brief Create AST value
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Create AST value
 * @param type Value type
 * @return New AST value or NULL on error
 */
ast_value* ast_value_create(int type) {
    ast_value* value = malloc(sizeof(ast_value));
    if (!value) {
        return NULL;
    }
    
    value->type = type;
    
    switch (type) {
        case AST_VAL_STRING:
            value->value.string_value = NULL;
            break;
        case AST_VAL_NUMBER:
            value->value.number_value = 0.0;
            break;
        case AST_VAL_BOOLEAN:
            value->value.boolean_value = false;
            break;
        case AST_VAL_NULL:
        default:
            break;
    }
    
    return value;
}