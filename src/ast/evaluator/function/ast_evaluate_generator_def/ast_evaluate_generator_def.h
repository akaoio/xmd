/**
 * @file ast_evaluate_generator_def.h
 * @brief Header for ast_evaluate_generator_def function
 * 
 * Genesis principle compliance: one function per file per directory
 */

#ifndef AST_EVALUATE_GENERATOR_DEF_H
#define AST_EVALUATE_GENERATOR_DEF_H

#include "ast.h"

/**
 * @brief Evaluate generator function definition
 * @param node Generator function AST node
 * @param evaluator AST evaluator context
 * @return Generator function object or NULL on error
 */
ast_value* ast_evaluate_generator_def(ast_node* node, ast_evaluator* evaluator);

#endif // AST_EVALUATE_GENERATOR_DEF_H