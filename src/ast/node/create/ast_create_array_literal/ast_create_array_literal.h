/**
 * @file ast_create_array_literal.h
 * @brief Declaration for ast_create_array_literal function
 * 
 * This file contains ONLY the ast_create_array_literal declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_ARRAY_LITERAL_H
#define AST_CREATE_ARRAY_LITERAL_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_array_literal(source_location loc);

#endif /* AST_CREATE_ARRAY_LITERAL_H */
