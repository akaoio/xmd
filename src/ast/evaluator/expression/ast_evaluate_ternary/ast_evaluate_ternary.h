/**
 * @file ast_evaluate_ternary.h
 * @brief Header for ast_evaluate_ternary function
 * 
 * This file contains ONLY the ast_evaluate_ternary function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_EVALUATE_TERNARY_H
#define XMD_AST_EVALUATE_TERNARY_H

#include "../../../../../../include/ast.h"

/**
 * @brief Evaluate ternary operator AST node
 * @param node Ternary AST node to evaluate
 * @param evaluator AST evaluator context
 * @return Result value or NULL on error
 */
ast_value* ast_evaluate_ternary(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_TERNARY_H */