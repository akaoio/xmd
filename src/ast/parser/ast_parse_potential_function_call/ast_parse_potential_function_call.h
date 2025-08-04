/**
 * @file ast_parse_potential_function_call.h
 * @brief Declaration for ast_parse_potential_function_call function
 * 
 * This file contains ONLY the ast_parse_potential_function_call declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_POTENTIAL_FUNCTION_CALL_H
#define AST_PARSE_POTENTIAL_FUNCTION_CALL_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_potential_function_call(const char** pos);

#endif /* AST_PARSE_POTENTIAL_FUNCTION_CALL_H */
