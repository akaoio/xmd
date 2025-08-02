/**
 * @file ast_evaluate_array_access.h
 * @brief Header for ast_evaluate_array_access function
 * 
 * This file contains ONLY the declaration for ast_evaluate_array_access function.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_ARRAY_ACCESS_H
#define AST_EVALUATE_ARRAY_ACCESS_H

#include "ast_node.h"
#include "ast_evaluator.h"
#include "ast_value.h"

/**
 * @brief Evaluate array access node (array[index])
 * @param node Array access AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_array_access(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_ARRAY_ACCESS_H */