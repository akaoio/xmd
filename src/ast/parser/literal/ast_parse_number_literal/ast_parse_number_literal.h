/**
 * @file ast_parse_number_literal.h
 * @brief Declaration for ast_parse_number_literal function
 * 
 * This file contains ONLY the ast_parse_number_literal declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_NUMBER_LITERAL_H
#define AST_PARSE_NUMBER_LITERAL_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_number_literal(const char** start, const char** pos);

#endif /* AST_PARSE_NUMBER_LITERAL_H */
