/**
 * @file ast_create_variable_ref.h
 * @brief Declaration for ast_create_variable_ref function
 * 
 * This file contains ONLY the ast_create_variable_ref declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_VARIABLE_REF_H
#define AST_CREATE_VARIABLE_REF_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_variable_ref(const char* name, source_location loc);

#endif /* AST_CREATE_VARIABLE_REF_H */
