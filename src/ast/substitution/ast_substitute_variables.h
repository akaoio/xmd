/**
 * @file ast_substitute_variables.h
 * @brief Declaration for ast_substitute_variables function
 * 
 * This file contains ONLY the ast_substitute_variables declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_SUBSTITUTE_VARIABLES_H
#define AST_SUBSTITUTE_VARIABLES_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
char* ast_substitute_variables(const char* text, store* variables);

#endif /* AST_SUBSTITUTE_VARIABLES_H */
