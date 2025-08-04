/**
 * @file ast_parse_yield.h
 * @brief Header for ast_parse_yield function
 * 
 * Genesis principle compliance: one function per file per directory
 */

#ifndef AST_PARSE_YIELD_H
#define AST_PARSE_YIELD_H

#include "ast.h"

/**
 * @brief Parse yield statement
 * @param pos Pointer to current parsing position (will be advanced)
 * @return AST node for yield statement or NULL on error
 */
ast_node* ast_parse_yield(const char** pos);

#endif // AST_PARSE_YIELD_H