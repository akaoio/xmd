/**
 * @file ast_value_create_boolean.c
 * @brief Implementation of ast_value_create_boolean function
 * 
 * This file contains ONLY the ast_value_create_boolean function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
ast_value* ast_value_create_boolean(bool value) {
    ast_value* val;
    XMD_MALLOC_CHECK(val, sizeof(ast_value));
    val->type = AST_VAL_BOOLEAN;
    val->value.boolean_value = value;
    return val;
}
