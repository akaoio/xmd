/**
 * @file ast_evaluate_date.h
 * @brief Header for ast_evaluate_date function
 * 
 * This file contains ONLY the ast_evaluate_date function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_EVALUATE_DATE_H
#define XMD_AST_EVALUATE_DATE_H

#include "../../../../../../include/ast.h"

/**
 * @brief Evaluate Date function call (Date.now, Date(), etc.)
 * @param node Function call AST node
 * @param evaluator AST evaluator context
 * @return Date value or NULL on error
 */
ast_value* ast_evaluate_date(ast_node* node, ast_evaluator* evaluator);

#endif /* XMD_AST_EVALUATE_DATE_H */