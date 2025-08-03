/**
 * @file ast_evaluate_conditional.c
 *
 *
 * @brief Implementation of ast_evaluate_conditional function
 * 
 * This file contains ONLY the ast_evaluate_conditional function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "variable.h"
#include "utils/common/common_macros.h"
/**
 * @brief Evaluate conditional node (if/elif/else)
 * @param node Conditional AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_conditional(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_CONDITIONAL, NULL, "ast_evaluate_conditional: Invalid node type");
    
    printf("DEBUG: Evaluating conditional node\n");
    // If this is an 'else' block (condition is NULL), execute the then_block
    if (!node->data.conditional.condition) {
        printf("DEBUG: Executing else block\n");
        if (node->data.conditional.then_block) {
            return ast_evaluate(node->data.conditional.then_block, evaluator);
        }
        return ast_value_create_string("");
    }
    
    // Evaluate the condition
    ast_value* condition_result = ast_evaluate(node->data.conditional.condition, evaluator);
    if (!condition_result) {
        printf("DEBUG: Condition evaluation failed\n");
        return NULL;
    }
    
    bool condition_true = false;
    // Determine if condition is true
    if (condition_result->type == AST_VAL_BOOLEAN) {
        condition_true = condition_result->value.boolean_value;
    } else if (condition_result->type == AST_VAL_NUMBER) {
        condition_true = (condition_result->value.number_value != 0.0);
    } else if (condition_result->type == AST_VAL_STRING) {
        condition_true = (condition_result->value.string_value && 
                         strlen(condition_result->value.string_value) > 0);
    }
    
    printf("DEBUG: Condition result: %s\n", condition_true ? "true" : "false");
    ast_value_free(condition_result);
    // Execute appropriate branch
    if (condition_true) {
        printf("DEBUG: Executing then block\n");
        if (node->data.conditional.then_block) {
            return ast_evaluate(node->data.conditional.then_block, evaluator);
        }
    } else {
        if (node->data.conditional.else_block) {
            return ast_evaluate(node->data.conditional.else_block, evaluator);
        }
    }
    
    // Return empty string if no block was executed
    return ast_value_create_string("");
}
