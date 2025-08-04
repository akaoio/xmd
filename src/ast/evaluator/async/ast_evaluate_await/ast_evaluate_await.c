/**
 * @file ast_evaluate_await.c
 *
 * @brief Implementation of ast_evaluate_await function
 * 
 * This file contains ONLY the ast_evaluate_await function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate await expression for async operations
 * @param node Await AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_await(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_AWAIT, NULL, "ast_evaluate_await: Invalid node type");
    
    // For now, await simply evaluates the expression synchronously
    // In a full async implementation, this would:
    // 1. Check if we're in an async context
    // 2. Handle promise-like objects
    // 3. Suspend execution until resolution
    
    // Evaluate the awaited expression
    ast_value* result = ast_evaluate(node->data.await.expression, evaluator);
    if (!result) {
        XMD_ERROR_RETURN(NULL, "Failed to evaluate await expression%s", "");
    }
    
    // For synchronous execution, just return the result directly
    return result;
}