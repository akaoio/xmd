/**
 * @file ast_value_create_string.c
 * @brief Implementation of ast_value_create_string function
 * 
 * This file contains ONLY the ast_value_create_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
ast_value* ast_value_create_string(const char* str) {
    ast_value* val = xmd_malloc(sizeof(ast_value));
    if (!val) return NULL;
    val->type = AST_VAL_STRING;
    val->value.string_value = xmd_strdup(str);
    return val;
}
