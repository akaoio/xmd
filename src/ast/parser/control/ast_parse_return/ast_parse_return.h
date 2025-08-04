/**
 * @file ast_parse_return.h
 * @brief Declaration of ast_parse_return function
 * 
 * This file contains ONLY the ast_parse_return function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_RETURN_H
#define AST_PARSE_RETURN_H

#include "ast_node.h"

/**
 * @brief Parse return statement: return expression
 * @param pos Pointer to current position in input
 * @return Return statement AST node or NULL
 */
ast_node* ast_parse_return(const char** pos);

#endif // AST_PARSE_RETURN_H