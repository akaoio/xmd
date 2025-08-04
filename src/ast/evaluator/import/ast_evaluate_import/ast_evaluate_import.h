/**
 * @file ast_evaluate_import.h
 * @brief Header for ast_evaluate_import function
 * 
 * Genesis principle compliance: One function per file.
 * Part of Phase 2 module system implementation.
 */

#ifndef AST_EVALUATE_IMPORT_H
#define AST_EVALUATE_IMPORT_H

#include "ast_node.h"
#include "ast_evaluator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Evaluate import statement - load module and import its exports
 * @param node Import AST node
 * @param evaluator Evaluator context
 * @return Empty string value (imports don't produce output)
 */
ast_value* ast_evaluate_import(ast_node* node, ast_evaluator* evaluator);

#ifdef __cplusplus
}
#endif

#endif /* AST_EVALUATE_IMPORT_H */