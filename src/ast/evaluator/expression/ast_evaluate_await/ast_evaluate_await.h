/**
 * @file ast_evaluate_await.h
 *
 * @brief Header for ast_evaluate_await function
 * 
 * This file contains ONLY declarations for ast_evaluate_await.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_AWAIT_H
#define AST_EVALUATE_AWAIT_H

#include "ast.h"

ast_value* ast_evaluate_await(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_AWAIT_H */