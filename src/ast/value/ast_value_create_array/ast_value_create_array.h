/**
 * @file ast_value_create_array.h
 * @brief Declaration for ast_value_create_array function
 * 
 * This file contains ONLY the ast_value_create_array declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_CREATE_ARRAY_H
#define AST_VALUE_CREATE_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_value*ast_value_create_array(void);

#endif /* AST_VALUE_CREATE_ARRAY_H */
