/**
 * @file ast_parse_statement_simple.h
 * @brief Declaration for ast_parse_statement_simple function
 * 
 * This file contains ONLY the ast_parse_statement_simple declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_STATEMENT_SIMPLE_H
#define AST_PARSE_STATEMENT_SIMPLE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_statement(const char** pos);

#endif /* AST_PARSE_STATEMENT_SIMPLE_H */
