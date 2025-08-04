/**
 * @file ast_evaluate_lambda.h
 * @brief Header for ast_evaluate_lambda function
 * 
 * This file contains ONLY the ast_evaluate_lambda function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_EVALUATE_LAMBDA_H
#define XMD_AST_EVALUATE_LAMBDA_H

#include "../../../../../../include/ast.h"

/**
 * @brief Evaluate lambda function AST node
 * @param node Lambda AST node to evaluate
 * @param evaluator AST evaluator context
 * @return Lambda function object or NULL on error
 */
ast_value* ast_evaluate_lambda(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_LAMBDA_H */