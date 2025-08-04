/**
 * @file ast_evaluate_loop_times.c
 *
 * @brief Implementation of ast_evaluate_loop_times function
 * 
 * This file contains ONLY the ast_evaluate_loop_times function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Evaluate loop N times (loop 5 times)
 * @param node Loop times AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_loop_times(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_LOOP_TIMES, NULL, "ast_evaluate_loop_times: Invalid node type");
    
    // Evaluate count expression
    ast_value* count_val = ast_evaluate(node->data.loop_times.count_expr, evaluator);
    if (!count_val || count_val->type != AST_VAL_NUMBER) {
        XMD_FREE_SAFE(count_val);
        XMD_ERROR_RETURN(NULL, "Loop times count must be a number%s", "");
    }
    
    int count = (int)floor(count_val->value.number_value);
    XMD_FREE_SAFE(count_val);
    
    if (count < 0) {
        XMD_ERROR_RETURN(NULL, "Loop times count cannot be negative%s", "");
    }
    
    ast_value* result = NULL;
    
    // Execute loop body N times
    for (int i = 0; i < count; i++) {
        XMD_FREE_SAFE(result);
        result = ast_evaluate(node->data.loop_times.body, evaluator);
        
        // Check for break/continue (would be handled by evaluator)
        if (evaluator->has_error) {
            break;
        }
    }
    
    return result;
}