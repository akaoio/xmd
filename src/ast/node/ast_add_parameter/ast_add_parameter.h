/**
 * @file ast_add_parameter.h
 * @brief Declaration for ast_add_parameter function
 * 
 * This file contains ONLY the ast_add_parameter declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_ADD_PARAMETER_H
#define AST_ADD_PARAMETER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
int ast_add_parameter(ast_node* function, const char* parameter);

#endif /* AST_ADD_PARAMETER_H */
