/**
 * @file ast_create_binary_op.h
 * @brief Declaration for ast_create_binary_op function
 * 
 * This file contains ONLY the ast_create_binary_op declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_BINARY_OP_H
#define AST_CREATE_BINARY_OP_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc);

#endif /* AST_CREATE_BINARY_OP_H */
