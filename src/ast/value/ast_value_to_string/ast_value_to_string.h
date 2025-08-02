/**
 * @file ast_value_to_string.h
 * @brief Declaration for ast_value_to_string function
 * 
 * This file contains ONLY the ast_value_to_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_TO_STRING_H
#define AST_VALUE_TO_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
char* ast_value_to_string(ast_value* value);

#endif /* AST_VALUE_TO_STRING_H */
