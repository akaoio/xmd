/**
 * @file ast_create_loop.h
 * @brief Declaration for ast_create_loop function
 * 
 * This file contains ONLY the ast_create_loop declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_LOOP_H
#define AST_CREATE_LOOP_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc);

#endif /* AST_CREATE_LOOP_H */
