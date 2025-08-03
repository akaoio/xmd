/**
 * @file ast_evaluate_loop.c
 *
 *
 * @brief Implementation of ast_evaluate_loop function
 * 
 * This file contains ONLY the ast_evaluate_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "store.h"
#include "variable.h"
/**
 * @brief Evaluate loop node (for variable in iterable)
 * @param node Loop AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_loop(ast_node* node, ast_evaluator* evaluator) {
    if (!node || node->type != AST_LOOP || !evaluator) {
        return NULL;
    }
    
    const char* loop_var = node->data.loop.variable;
    ast_node* iterable = node->data.loop.iterable;
    if (!loop_var || !iterable) {
        return NULL;
    }
    
    // For now, handle array literals as iterables
    if (iterable->type != AST_ARRAY_LITERAL) {
        printf("DEBUG: Unsupported iterable type: %d\n", iterable->type);
        return ast_value_create_string("");
    }
    
    ast_value* result = ast_value_create_string("");
    // Iterate over array elements
    for (size_t i = 0; i < iterable->data.array_literal.element_count; i++) {
        ast_node* element = iterable->data.array_literal.elements[i];
        if (!element) continue;
        
        // Loop iteration
        // Evaluate the element to get its value
        ast_value* element_value = ast_evaluate(element, evaluator);
        if (!element_value) continue;
        // Set the loop variable to the current element value
        variable* loop_var_obj = NULL;
        if (element_value->type == AST_VAL_STRING) {
            loop_var_obj = variable_create_string(element_value->value.string_value);
        } else if (element_value->type == AST_VAL_NUMBER) {
            loop_var_obj = variable_create_number(element_value->value.number_value);
        } else if (element_value->type == AST_VAL_BOOLEAN) {
            loop_var_obj = variable_create_boolean(element_value->value.boolean_value);
        }
        if (loop_var_obj) {
            store_set(evaluator->variables, loop_var, loop_var_obj);
            variable_unref(loop_var_obj); // store_set takes ownership
        }
        
        ast_value_free(element_value);
        // Execute loop body if it exists
        if (node->data.loop.body) {
            // Execute loop body
            ast_value* body_result = ast_evaluate(node->data.loop.body, evaluator);
            if (body_result) {
                // The body result represents the output of all statements in the loop body
                // Individual print statements handle their own output
                ast_value_free(body_result);
            }
        }
        // Loop iteration completed
    }
    
    return result;
}
