/**
 * @file ast_evaluate_for_range.c
 *
 * @brief Implementation of ast_evaluate_for_range function
 * 
 * This file contains ONLY the ast_evaluate_for_range function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate for range loop (for i in 1..5)
 * @param node For range AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_for_range(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FOR_RANGE, NULL, "ast_evaluate_for_range: Invalid node type");
    
    // Evaluate start and end expressions
    ast_value* start_val = ast_evaluate(node->data.for_range.start_expr, evaluator);
    if (!start_val || start_val->type != AST_VAL_NUMBER) {
        XMD_FREE_SAFE(start_val);
        XMD_ERROR_RETURN(NULL, "For range start must be a number%s", "");
    }
    
    ast_value* end_val = ast_evaluate(node->data.for_range.end_expr, evaluator);
    if (!end_val || end_val->type != AST_VAL_NUMBER) {
        XMD_FREE_SAFE(start_val);
        XMD_FREE_SAFE(end_val);
        XMD_ERROR_RETURN(NULL, "For range end must be a number%s", "");
    }
    
    int start = (int)floor(start_val->value.number_value);
    int end = (int)floor(end_val->value.number_value);
    
    XMD_FREE_SAFE(start_val);
    XMD_FREE_SAFE(end_val);
    
    ast_value* result = NULL;
    
    // Execute loop for each value in range
    for (int i = start; i <= end; i++) {
        // Set loop variable
        variable* loop_var = variable_create_number((double)i);
        if (loop_var) {
            store_set(evaluator->variables, node->data.for_range.variable, loop_var);
            variable_unref(loop_var);
        }
        
        // Execute body
        XMD_FREE_SAFE(result);
        result = ast_evaluate(node->data.for_range.body, evaluator);
        
        // Check for break/continue
        if (evaluator->has_error) {
            break;
        }
    }
    
    return result;
}