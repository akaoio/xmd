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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Evaluate loop node (for variable in iterable)
 * @param node Loop AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_loop(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_LOOP, NULL, "ast_evaluate_loop: Invalid node type");
    
    const char* loop_var = node->data.loop.variable;
    ast_node* iterable = node->data.loop.iterable;
    XMD_VALIDATE_PARAMS_2(NULL, loop_var, iterable);
    
    // Check if this is indexed iteration (variable contains comma)
    bool is_indexed = false;
    char* index_var = NULL;
    char* item_var = NULL;
    
    char* comma_pos = strchr(loop_var, ',');
    if (comma_pos) {
        is_indexed = true;
        size_t index_len = comma_pos - loop_var;
        size_t item_len = strlen(comma_pos + 1);
        
        XMD_MALLOC_DYNAMIC(index_var, index_len + 1, NULL);
        XMD_MALLOC_DYNAMIC(item_var, item_len + 1, NULL);
        
        memcpy(index_var, loop_var, index_len);
        index_var[index_len] = '\0';
        strcpy(item_var, comma_pos + 1);
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
        if (!element) continue; // Skip NULL elements in array
        
        // Loop iteration
        // Evaluate the element to get its value
        ast_value* element_value = ast_evaluate(element, evaluator);
        if (!element_value) continue; // Skip if evaluation fails
        // Set the loop variable(s) to the current element value and/or index
        if (is_indexed) {
            // Set index variable to current index
            variable* index_var_obj = variable_create_number((double)i);
            if (index_var_obj) {
                store_set(evaluator->variables, index_var, index_var_obj);
                variable_unref(index_var_obj);
            }
            
            // Set item variable to current element value
            variable* item_var_obj = NULL;
            if (element_value->type == AST_VAL_STRING) {
                item_var_obj = variable_create_string(element_value->value.string_value);
            } else if (element_value->type == AST_VAL_NUMBER) {
                item_var_obj = variable_create_number(element_value->value.number_value);
            } else if (element_value->type == AST_VAL_BOOLEAN) {
                item_var_obj = variable_create_boolean(element_value->value.boolean_value);
            }
            if (item_var_obj) {
                store_set(evaluator->variables, item_var, item_var_obj);
                variable_unref(item_var_obj);
            }
        } else {
            // Standard iteration - set loop variable to current element value
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
                variable_unref(loop_var_obj);
            }
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
    
    // Cleanup allocated variables
    XMD_FREE_SAFE(index_var);
    XMD_FREE_SAFE(item_var);
    
    return result;
}
