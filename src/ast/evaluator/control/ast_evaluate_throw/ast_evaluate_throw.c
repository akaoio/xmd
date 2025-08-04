/**
 * @file ast_evaluate_throw.c
 *
 * @brief Implementation of ast_evaluate_throw function
 * 
 * This file contains ONLY the ast_evaluate_throw function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate throw statement
 * @param node Throw AST node
 * @param evaluator Evaluator context
 * @return NULL (throw always sets error state)
 */
ast_value* ast_evaluate_throw(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_THROW, NULL, "ast_evaluate_throw: Invalid node type");
    
    // Evaluate the exception expression
    ast_value* exception = ast_evaluate(node->data.throw_stmt.exception, evaluator);
    if (!exception) {
        XMD_ERROR_RETURN(NULL, "Failed to evaluate throw expression%s", "");
    }
    
    // Convert exception to string
    char* exception_message = ast_value_to_string(exception);
    XMD_FREE_SAFE(exception);
    
    if (!exception_message) {
        XMD_ERROR_RETURN(NULL, "Failed to convert exception to string%s", "");
    }
    
    // Set error state in evaluator
    evaluator->has_error = true;
    XMD_FREE_SAFE(evaluator->error_message);
    evaluator->error_message = exception_message;
    
    return NULL;
}