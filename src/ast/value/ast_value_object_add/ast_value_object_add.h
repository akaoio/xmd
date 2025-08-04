/**
 * @file ast_value_object_add.h
 * @brief Declaration for ast_value_object_add function
 * 
 * This file contains ONLY the ast_value_object_add declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_OBJECT_ADD_H
#define AST_VALUE_OBJECT_ADD_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */
typedef struct ast_value ast_value;

/* Function declaration */
int ast_value_object_add(ast_value* object, const char* key, ast_value* value);

#endif /* AST_VALUE_OBJECT_ADD_H */