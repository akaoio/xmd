/**
 * @file ast_parse_comparison_expression.h
 * @brief Declaration for ast_parse_comparison_expression function
 * 
 * This file contains ONLY the ast_parse_comparison_expression declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_COMPARISON_EXPRESSION_H
#define AST_PARSE_COMPARISON_EXPRESSION_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_comparison_expression(const char* expr);

#endif /* AST_PARSE_COMPARISON_EXPRESSION_H */
