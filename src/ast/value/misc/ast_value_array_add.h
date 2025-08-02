/**
 * @file ast_value_array_add.h
 * @brief Declaration for ast_value_array_add function
 * 
 * This file contains ONLY the ast_value_array_add declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_ARRAY_ADD_H
#define AST_VALUE_ARRAY_ADD_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
int ast_value_array_add(ast_value* array, ast_value* element);

#endif /* AST_VALUE_ARRAY_ADD_H */
