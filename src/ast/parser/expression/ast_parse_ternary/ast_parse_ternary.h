/**
 * @file ast_parse_ternary.h
 * @brief Header for ast_parse_ternary function
 * 
 * This file contains ONLY the ast_parse_ternary function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_PARSE_TERNARY_H
#define XMD_AST_PARSE_TERNARY_H

#include "../../../../../../include/ast.h"

/**
 * @brief Parse ternary operator expression
 * @param pos Pointer to current position in input (will be advanced)
 * @return Ternary AST node or NULL if not a ternary expression
 */
ast_node* ast_parse_ternary(const char** pos);

#endif /* XMD_AST_PARSE_TERNARY_H */