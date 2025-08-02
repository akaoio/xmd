/**
 * @file ast_create_identifier.h
 * @brief Declaration for ast_create_identifier function
 * 
 * This file contains ONLY the ast_create_identifier declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_IDENTIFIER_H
#define AST_CREATE_IDENTIFIER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_identifier(const char* name, source_location loc);

#endif /* AST_CREATE_IDENTIFIER_H */
