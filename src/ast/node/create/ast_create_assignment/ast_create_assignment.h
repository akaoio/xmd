/**
 * @file ast_create_assignment.h
 * @brief Declaration for ast_create_assignment function
 * 
 * This file contains ONLY the ast_create_assignment declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_ASSIGNMENT_H
#define AST_CREATE_ASSIGNMENT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc);

#endif /* AST_CREATE_ASSIGNMENT_H */
