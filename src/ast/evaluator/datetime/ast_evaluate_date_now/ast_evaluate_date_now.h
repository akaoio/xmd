/**
 * @file ast_evaluate_date_now.h
 * @brief Header for ast_evaluate_date_now function
 */

#ifndef XMD_AST_EVALUATE_DATE_NOW_H
#define XMD_AST_EVALUATE_DATE_NOW_H

#include "ast.h"

/**
 * @brief Evaluate Date.now() - returns current timestamp
 * @param node Function call AST node
 * @param evaluator Evaluator context
 * @return AST value with current timestamp or NULL on error
 */
ast_value* ast_evaluate_date_now(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_DATE_NOW_H */