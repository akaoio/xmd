/**
 * @file ast_parse_single_value.h
 * @brief Declaration for ast_parse_single_value function
 * 
 * This file contains ONLY the ast_parse_single_value declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_SINGLE_VALUE_H
#define AST_PARSE_SINGLE_VALUE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_single_value(const char** pos);

#endif /* AST_PARSE_SINGLE_VALUE_H */
