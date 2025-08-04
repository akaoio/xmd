/**
 * @file ast_parse_indented_block.h
 * @brief Declaration of ast_parse_indented_block function
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 */

#ifndef AST_PARSE_INDENTED_BLOCK_H
#define AST_PARSE_INDENTED_BLOCK_H

#include "ast_node.h"

/**
 * @brief Parse an indented block of statements
 * @param pos Pointer to current position in input
 * @param min_indent Minimum expected indentation level
 * @return Block node containing statements or NULL
 */
ast_node* ast_parse_indented_block(const char** pos, int min_indent);

#endif /* AST_PARSE_INDENTED_BLOCK_H */