/**
 * @file ast_value_create_boolean.h
 * @brief Declaration for ast_value_create_boolean function
 * 
 * This file contains ONLY the ast_value_create_boolean declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_CREATE_BOOLEAN_H
#define AST_VALUE_CREATE_BOOLEAN_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_value* ast_value_create_boolean(bool value);

#endif /* AST_VALUE_CREATE_BOOLEAN_H */
