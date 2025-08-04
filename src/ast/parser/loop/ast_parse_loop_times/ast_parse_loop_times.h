/**
 * @file ast_parse_loop_times.h
 *
 * @brief Header for ast_parse_loop_times function
 * 
 * This file contains ONLY the ast_parse_loop_times function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_LOOP_TIMES_H
#define AST_PARSE_LOOP_TIMES_H

#include "ast_node.h"

/**
 * @brief Parse "loop N times" syntax
 * @param pos Pointer to current position
 * @return Loop AST node or NULL
 */
ast_node* ast_parse_loop_times(const char** pos);

#endif // AST_PARSE_LOOP_TIMES_H