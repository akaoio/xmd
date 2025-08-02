/**
 * @file ast_create_function_def.h
 * @brief Declaration for ast_create_function_def function
 * 
 * This file contains ONLY the ast_create_function_def declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_FUNCTION_DEF_H
#define AST_CREATE_FUNCTION_DEF_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_function_def(const char* name, bool is_async, source_location loc);

#endif /* AST_CREATE_FUNCTION_DEF_H */
