/**
 * @file ast_parse_indexed_loop.h
 * @brief Header for ast_parse_indexed_loop function
 * 
 * This file contains ONLY the ast_parse_indexed_loop function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_PARSE_INDEXED_LOOP_H
#define XMD_AST_PARSE_INDEXED_LOOP_H

#include "../../../../../../include/ast.h"

/**
 * @brief Parse indexed loop statement "for i, item in items"
 * @param pos Pointer to current position in input (will be advanced)
 * @return Loop AST node or NULL if not an indexed loop
 */
ast_node* ast_parse_indexed_loop(const char** pos);

#endif /* XMD_AST_PARSE_INDEXED_LOOP_H */