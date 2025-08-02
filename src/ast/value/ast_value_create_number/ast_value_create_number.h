/**
 * @file ast_value_create_number.h
 * @brief Declaration for ast_value_create_number function
 * 
 * This file contains ONLY the ast_value_create_number declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_CREATE_NUMBER_H
#define AST_VALUE_CREATE_NUMBER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_value* ast_value_create_number(double value);

#endif /* AST_VALUE_CREATE_NUMBER_H */
