/**
 * @file ast_value_free.h
 * @brief Declaration for ast_value_free function
 * 
 * This file contains ONLY the ast_value_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_FREE_H
#define AST_VALUE_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
void ast_value_free(ast_value* value);

#endif /* AST_VALUE_FREE_H */
