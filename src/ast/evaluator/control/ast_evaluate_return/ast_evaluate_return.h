/**
 * @file ast_evaluate_return.h
 * @brief Declaration of ast_evaluate_return function
 * 
 * This file contains ONLY the ast_evaluate_return function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_RETURN_H
#define AST_EVALUATE_RETURN_H

#include "ast_node.h"
#include "ast_evaluator.h"
#include "ast_value.h"

/**
 * @brief Evaluate return statement
 * @param node Return statement AST node
 * @param evaluator Evaluator context
 * @return Return value or NULL
 */
ast_value* ast_evaluate_return(ast_node* node, ast_evaluator* evaluator);

#endif // AST_EVALUATE_RETURN_H