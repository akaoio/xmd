/**
 * @file ast_evaluate_assignment.c
 *
 *
 * @brief Implementation of ast_evaluate_assignment function
 * 
 * This file contains ONLY the ast_evaluate_assignment function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "error.h"
#include "store.h"
#include "variable.h"
#include "utils/common/common_macros.h"
/**
 * @brief Evaluate assignment node
 * @param node Assignment node
 * @param evaluator Evaluator context
 * @return Assigned value or NULL
 */
int ast_evaluate_assignment(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(-1, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_ASSIGNMENT, -1, "ast_evaluate_assignment: Invalid node type");
    
    ast_value* value = ast_evaluate(node->data.assignment.value, evaluator);
    if (!value || evaluator->error_message) {
        printf("[ERROR] ast_evaluate_assignment: Failed to evaluate assignment value\n");
        return -1;
    }
    
    // Store in evaluator's variable store
    if (evaluator->variables) {
        // Convert ast_value to variable using existing function
        variable* var = ast_value_to_variable(value);
        
        if (var) {
            store_set(evaluator->variables, node->data.assignment.variable, var);
            variable_unref(var); // store_set takes ownership
        } else {
        }
    }
    
    // Don't free the value here - it's handled by the caller in ast_evaluate
    return 0;
}
