/**
 * @file ast_add_element.h
 * @brief Declaration for ast_add_element function
 * 
 * This file contains ONLY the ast_add_element declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_ADD_ELEMENT_H
#define AST_ADD_ELEMENT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
int ast_add_element(ast_node* array, ast_node* element);

#endif /* AST_ADD_ELEMENT_H */
