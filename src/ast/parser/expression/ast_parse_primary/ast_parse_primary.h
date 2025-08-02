/**
 * @file ast_parse_primary.h
 * @brief Declaration for ast_parse_primary function
 * 
 * This file contains ONLY the ast_parse_primary declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_PRIMARY_H
#define AST_PARSE_PRIMARY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_parse_primary(parser_state* state);

#endif /* AST_PARSE_PRIMARY_H */
