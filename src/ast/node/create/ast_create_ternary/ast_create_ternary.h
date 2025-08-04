/**
 * @file ast_create_ternary.h
 * @brief Header for ast_create_ternary function
 */

#ifndef XMD_AST_CREATE_TERNARY_H
#define XMD_AST_CREATE_TERNARY_H

#include "ast.h"

/**
 * @brief Create ternary operator AST node
 * @param condition Condition expression
 * @param true_expr True case expression  
 * @param false_expr False case expression
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_ternary(ast_node* condition, ast_node* true_expr, ast_node* false_expr, source_location loc);

#endif /* XMD_AST_CREATE_TERNARY_H */