/**
 * @file ast_parse_array_assignment.h
 * @brief Declaration for ast_parse_array_assignment function
 * 
 * This file contains ONLY the ast_parse_array_assignment declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_ARRAY_ASSIGNMENT_H
#define AST_PARSE_ARRAY_ASSIGNMENT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_array_assignment(const char** pos, const char* array_name);

#endif /* AST_PARSE_ARRAY_ASSIGNMENT_H */
