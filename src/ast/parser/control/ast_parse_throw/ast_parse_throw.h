/**
 * @file ast_parse_throw.h
 * @brief Header for ast_parse_throw function
 * 
 * This file contains ONLY the ast_parse_throw function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_PARSE_THROW_H
#define XMD_AST_PARSE_THROW_H

#include "../../../../../../include/ast.h"

/**
 * @brief Parse throw statement
 * @param pos Pointer to current position in input (will be advanced)
 * @return Throw AST node or NULL on error
 */
ast_node* ast_parse_throw(const char** pos);

#endif /* XMD_AST_PARSE_THROW_H */