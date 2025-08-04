/**
 * @file ast_evaluate_try_catch.c
 *
 * @brief Implementation of ast_evaluate_try_catch function
 * 
 * This file contains ONLY the ast_evaluate_try_catch function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate try-catch error handling
 * @param node Try-catch AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_try_catch(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_TRY_CATCH, NULL, "ast_evaluate_try_catch: Invalid node type");
    
    ast_value* result = NULL;
    
    // Save current error state
    bool prev_error = evaluator->has_error;
    char* prev_message = evaluator->error_message;
    evaluator->has_error = false;
    evaluator->error_message = NULL;
    
    // Try to execute the try block
    result = ast_evaluate(node->data.try_catch.try_block, evaluator);
    
    // If an error occurred in try block, execute catch block
    if (evaluator->has_error) {
        // Store exception in catch variable
        if (node->data.try_catch.catch_variable && evaluator->error_message) {
            variable* exception_var = variable_create_string(evaluator->error_message);
            if (exception_var) {
                store_set(evaluator->variables, node->data.try_catch.catch_variable, exception_var);
                variable_unref(exception_var);
            }
        }
        
        // Clear error state and execute catch block
        XMD_FREE_SAFE(evaluator->error_message);
        evaluator->has_error = false;
        evaluator->error_message = NULL;
        
        // Free failed try result and execute catch block
        XMD_FREE_SAFE(result);
        result = ast_evaluate(node->data.try_catch.catch_block, evaluator);
    }
    
    // Restore previous error state if no new errors
    if (!evaluator->has_error) {
        evaluator->has_error = prev_error;
        evaluator->error_message = prev_message;
    } else {
        // Clean up previous error message if we have a new error
        XMD_FREE_SAFE(prev_message);
    }
    
    return result;
}