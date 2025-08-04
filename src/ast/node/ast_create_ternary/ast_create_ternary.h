/**
 * @file ast_create_ternary.h
 * @brief Header for ast_create_ternary function
 * 
 * This file contains ONLY the ast_create_ternary function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_CREATE_TERNARY_H
#define XMD_AST_CREATE_TERNARY_H

#include "../../../../../../include/ast.h"

/**
 * @brief Create ternary operator AST node
 * @param condition Condition expression to evaluate
 * @param true_expr Expression to return if condition is true
 * @param false_expr Expression to return if condition is false
 * @param loc Source location
 * @return New ternary AST node or NULL on error
 */
ast_node* ast_create_ternary(ast_node* condition, ast_node* true_expr, ast_node* false_expr, source_location loc);

#endif /* XMD_AST_CREATE_TERNARY_H */