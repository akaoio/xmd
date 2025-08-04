/**
 * @file ast_evaluate_destructure.c
 *
 * @brief Implementation of ast_evaluate_destructure function
 * 
 * This file contains ONLY the ast_evaluate_destructure function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Evaluate destructuring assignment
 * @param node Destructuring AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_destructure(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_DESTRUCTURE, NULL, "ast_evaluate_destructure: Invalid node type");
    
    // Evaluate source expression
    ast_value* source = ast_evaluate(node->data.destructure.source_expr, evaluator);
    if (!source) {
        return NULL;
    }
    
    // Handle array destructuring
    if (!node->data.destructure.is_object) {
        if (source->type != AST_VAL_ARRAY) {
            ast_value_free(source);
            return NULL;
        }
        
        // Assign array elements to target variables
        for (size_t i = 0; i < node->data.destructure.target_count; i++) {
            const char* target_name = node->data.destructure.target_names[i];
            if (!target_name) continue;
            
            variable* var = NULL;
            if (i < source->value.array_value.element_count) {
                // Convert AST value to variable
                var = ast_value_to_variable(source->value.array_value.elements[i]);
            } else {
                // Create null variable for missing elements
                var = variable_create_null();
            }
            
            if (var) {
                store_set(evaluator->variables, target_name, var);
                variable_unref(var);
            }
        }
        
        // Handle rest parameter for arrays
        if (node->data.destructure.rest_name) {
            variable* rest_array = variable_create_array();
            if (rest_array) {
                // Add remaining elements to rest array
                for (size_t i = node->data.destructure.target_count; 
                     i < source->value.array_value.element_count; i++) {
                    variable* element = ast_value_to_variable(source->value.array_value.elements[i]);
                    if (element) {
                        variable_array_add(rest_array, element);
                        variable_unref(element);
                    }
                }
                store_set(evaluator->variables, node->data.destructure.rest_name, rest_array);
                variable_unref(rest_array);
            }
        }
    } 
    // Handle object destructuring
    else {
        // For object destructuring, we expect pairs: source_key target_var
        // Example: destructure user name username, age userage
        variable* source_var = ast_value_to_variable(source);
        if (!source_var || variable_get_type(source_var) != VARIABLE_TYPE_OBJECT) {
            XMD_FREE_SAFE(source_var);
            ast_value_free(source);
            return NULL;
        }
        
        // Process pairs of (source_key, target_var)
        for (size_t i = 0; i + 1 < node->data.destructure.target_count; i += 2) {
            const char* source_key = node->data.destructure.target_names[i];
            const char* target_var = node->data.destructure.target_names[i + 1];
            
            if (!source_key || !target_var) continue;
            
            // Get value from source object
            variable* value = variable_object_get(source_var, source_key);
            if (value) {
                store_set(evaluator->variables, target_var, value);
            } else {
                // Create null variable for missing keys
                variable* null_var = variable_create_null();
                if (null_var) {
                    store_set(evaluator->variables, target_var, null_var);
                    variable_unref(null_var);
                }
            }
        }
        
        variable_unref(source_var);
    }
    
    ast_value_free(source);
    
    // Return null value (destructuring is a statement, not expression)
    return ast_value_create_string("");
}