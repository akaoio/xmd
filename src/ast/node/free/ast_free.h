/**
 * @file ast_free.h
 * @brief Declaration for ast_free function
 * 
 * This file contains ONLY the ast_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_FREE_H
#define AST_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
void ast_free(ast_node* node);

#endif /* AST_FREE_H */
