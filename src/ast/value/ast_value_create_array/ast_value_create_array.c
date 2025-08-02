/**
 * @file ast_value_create_array.c
 * @brief Implementation of ast_value_create_array function
 * 
 * This file contains ONLY the ast_value_create_array function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
ast_value* ast_value_create_array(void) {
    ast_value* val = xmd_malloc(sizeof(ast_value));
    if (!val) return NULL;
    val->type = AST_VAL_ARRAY;
    val->value.array_value.elements = NULL;
    val->value.array_value.element_count = 0;
    return val;
}
