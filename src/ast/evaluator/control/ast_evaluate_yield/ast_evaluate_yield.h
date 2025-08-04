/**
 * @file ast_evaluate_yield.h
 * @brief Header for ast_evaluate_yield function
 * 
 * Genesis principle compliance: one function per file per directory
 */

#ifndef AST_EVALUATE_YIELD_H
#define AST_EVALUATE_YIELD_H

#include "ast.h"

/**
 * @brief Evaluate yield statement
 * @param node Yield AST node
 * @param evaluator AST evaluator context
 * @return Yielded value or NULL on error
 */
ast_value* ast_evaluate_yield(ast_node* node, ast_evaluator* evaluator);

#endif // AST_EVALUATE_YIELD_H