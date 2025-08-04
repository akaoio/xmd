/**
 * @file ast_evaluate_class_def.h
 * @brief Header for ast_evaluate_class_def function
 */

#ifndef AST_EVALUATE_CLASS_DEF_H
#define AST_EVALUATE_CLASS_DEF_H

#include "ast.h"
#include "ast_evaluator.h"

/**
 * @brief Evaluate class definition node
 * @param node Class definition AST node
 * @param evaluator Evaluator context
 * @return ast_value* Result value
 */
ast_value* ast_evaluate_class_def(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_CLASS_DEF_H */