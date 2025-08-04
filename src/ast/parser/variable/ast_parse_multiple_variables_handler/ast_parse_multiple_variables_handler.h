/**
 * @file ast_parse_multiple_variables_handler.h
 * @brief Declaration for ast_parse_multiple_variables_handler function
 * 
 * This file contains ONLY the ast_parse_multiple_variables_handler declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_MULTIPLE_VARIABLES_HANDLER_H
#define AST_PARSE_MULTIPLE_VARIABLES_HANDLER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_multiple_variables_handler(const char** pos, const char* first_name);

#endif /* AST_PARSE_MULTIPLE_VARIABLES_HANDLER_H */
