/**
 * @file ast_evaluate_throw.h
 * @brief Header for ast_evaluate_throw function
 */

#ifndef XMD_AST_EVALUATE_THROW_H
#define XMD_AST_EVALUATE_THROW_H

#include "ast.h"

/**
 * @brief Evaluate throw statement
 * @param node Throw AST node
 * @param evaluator Evaluator context
 * @return NULL (throw always sets error state)
 */
ast_value* ast_evaluate_throw(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_THROW_H */