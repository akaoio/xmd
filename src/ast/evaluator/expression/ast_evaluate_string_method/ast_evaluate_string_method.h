/**
 * @file ast_evaluate_string_method.h
 * @brief Header for ast_evaluate_string_method function
 */

#ifndef XMD_AST_EVALUATE_STRING_METHOD_H
#define XMD_AST_EVALUATE_STRING_METHOD_H

#include "ast.h"

/**
 * @brief Evaluate string method calls (.upper, .lower, .split, .join, etc.)
 * @param node String method AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_string_method(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_STRING_METHOD_H */