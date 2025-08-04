/**
 * @file ast_evaluate_try_catch.h
 * @brief Header for ast_evaluate_try_catch function
 */

#ifndef XMD_AST_EVALUATE_TRY_CATCH_H
#define XMD_AST_EVALUATE_TRY_CATCH_H

#include "ast.h"

/**
 * @brief Evaluate try-catch error handling
 * @param node Try-catch AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_try_catch(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_TRY_CATCH_H */