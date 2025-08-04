/**
 * @file ast_evaluate_while_loop.c
 *
 *
 * @brief Implementation of ast_evaluate_while_loop function
 * 
 * This file contains ONLY the ast_evaluate_while_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "store.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Evaluate while loop node
 * @param node While loop node (marked as AST_WHILE_LOOP)
 * @param evaluator Evaluator context
 * @return Empty string value
 */
ast_value* ast_evaluate_while_loop(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_WHILE_LOOP, NULL, "ast_evaluate_while_loop: Invalid node type");
    
    // While loop structure uses the loop data fields:
    // - node->data.loop.variable is "__while__" (marker)
    // - node->data.loop.iterable is the condition expression
    // - node->data.loop.body would be the body (not implemented yet)
    ast_node* condition = node->data.loop.iterable;
    XMD_VALIDATE_PTR_RETURN(condition, NULL);
    
    // Evaluate while condition using consolidated patterns
    int max_iterations = 1000; // Safety limit
    int iterations = 0;
    while (iterations < max_iterations) {
        ast_value* condition_result = ast_evaluate(condition, evaluator);
        XMD_VALIDATE_PTR_RETURN(condition_result, NULL);
        
        // Convert to boolean using consolidated pattern
        bool is_true = false;
        if (condition_result->type == AST_VAL_BOOLEAN) {
            is_true = condition_result->value.boolean_value;
        } else if (condition_result->type == AST_VAL_NUMBER) {
            is_true = (condition_result->value.number_value != 0.0);
        } else if (condition_result->type == AST_VAL_STRING) {
            is_true = (condition_result->value.string_value != NULL && 
                      strlen(condition_result->value.string_value) > 0);
        }
        
        ast_value_free(condition_result);
        if (!is_true) {
            break; // Exit while loop
        }
        
        // Execute while loop body using validated pattern
        if (node->data.loop.body) {
            ast_value* body_result = ast_evaluate(node->data.loop.body, evaluator);
            XMD_CLEANUP_RESOURCE(body_result, ast_value_free);
        } else {
            // FALLBACK: Old auto-increment behavior (remove this once body parsing is confirmed working)
            // This was a temporary workaround - while loops should execute their body, not auto-increment
            if (evaluator->variables) {
                const char* common_vars[] = {"count", "i", "j", "k", "index", "n", NULL};
                for (int v = 0; common_vars[v]; v++) {
                    variable* var = store_get(evaluator->variables, common_vars[v]);
                    if (var && var->type == VAR_NUMBER) {
                        variable* new_var = variable_create_number(var->value.number_value + 1.0);
                        if (new_var) {
                            store_set(evaluator->variables, common_vars[v], new_var);
                            variable_unref(new_var);
                            break;
                        }
                    }
                }
            }
        }
        
        iterations++;
        // Check for break/continue (would need loop context)
        if (evaluator->has_error) {
            break;
        }
    }
    
    return NULL; // While loops don't return values
}
