/**
 * @file ast_value_create_object.c
 * @brief Implementation of ast_value_create_object function
 * 
 * This file contains ONLY the ast_value_create_object function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create object ast_value
 * @return Object ast_value or NULL on failure
 */
ast_value* ast_value_create_object(void) {
    ast_value* val;
    XMD_AST_CREATE_VALUE(val, AST_VAL_OBJECT, NULL);
    val->value.object_value.keys = NULL;
    val->value.object_value.values = NULL;
    val->value.object_value.pair_count = 0;
    return val;
}