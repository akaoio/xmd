/**
 * @file ast_add_argument.h
 * @brief Declaration for ast_add_argument function
 * 
 * This file contains ONLY the ast_add_argument declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_ADD_ARGUMENT_H
#define AST_ADD_ARGUMENT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
int ast_add_argument(ast_node* node, ast_node* argument);

#endif /* AST_ADD_ARGUMENT_H */
