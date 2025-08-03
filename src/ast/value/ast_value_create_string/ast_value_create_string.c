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
#include "utils/common/common_macros.h"
ast_value* ast_value_create_string(const char* str) {
    XMD_VALIDATE_PTRS(NULL, str);
    ast_value* val;
    XMD_MALLOC_CHECK(val, sizeof(ast_value));
    val->type = AST_VAL_STRING;
    XMD_STRDUP_CHECK(val->value.string_value, str);
    return val;
}
