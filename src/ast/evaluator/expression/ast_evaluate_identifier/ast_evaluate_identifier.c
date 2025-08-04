/**
 * @file ast_evaluate_identifier.c
 *
 *
 * @brief Implementation of ast_evaluate_identifier function
 * 
 * This file contains ONLY the ast_evaluate_identifier function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate identifier node
 * @param node Identifier AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_identifier(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_IDENTIFIER, NULL, "ast_evaluate_identifier: Invalid node type");
    
    const char* var_name = node->data.identifier.name;
    variable* var = store_get(evaluator->variables, var_name);
    if (!var) {
        // Check if this identifier is a parameterless function
        if (evaluator->functions) {
            variable* func_var = store_get(evaluator->functions, var_name);
            if (func_var) {
                // This is a parameterless function call
                // Create a function call AST node and evaluate it
                ast_node* func_call_node;
                func_call_node = xmd_malloc(sizeof(ast_node));
                XMD_VALIDATE_PTR_RETURN(func_call_node, NULL);
                memset(func_call_node, 0, sizeof(ast_node));
                func_call_node->type = AST_FUNCTION_CALL;
                func_call_node->data.function_call.name = xmd_strdup(var_name);
                func_call_node->data.function_call.arguments = NULL;
                func_call_node->data.function_call.argument_count = 0;
                
                // Import the function evaluation
                extern ast_value* ast_evaluate_function_call(ast_node* node, ast_evaluator* evaluator);
                ast_value* result = ast_evaluate_function_call(func_call_node, evaluator);
                
                // Clean up
                XMD_FREE_SAFE(func_call_node->data.function_call.name);
                XMD_FREE_SAFE(func_call_node);
                
                return result;
            }
        }
        return ast_value_create_string(""); // Return empty string for undefined variables
    }
    
    // Convert variable to AST value based on its actual type
    variable_type var_type = variable_get_type(var);
    switch (var_type) {
        case VAR_STRING: {
            const char* str_val = variable_get_string(var);
            return ast_value_create_string(str_val ? str_val : "");
        }
        case VAR_NUMBER: {
            double num_val = variable_get_number(var);
            return ast_value_create_number(num_val);
        }
        case VAR_BOOLEAN: {
            bool bool_val = variable_get_boolean(var);
            return ast_value_create_boolean(bool_val);
        }
        case VAR_ARRAY:
        case VAR_OBJECT: {
            // Handle array by converting all elements to a comma-separated string
            
            // For now, use variable_to_string to get some representation
            const char* var_str = variable_to_string(var);
            if (var_str) {
                return ast_value_create_string(var_str);
            }
            // If variable_to_string doesn't work well for arrays, we'll need to
            // implement proper array-to-string conversion here
            return ast_value_create_string("[array]");
        }
        default: {
            // Fallback to string conversion
            const char* var_str = variable_to_string(var);
            return ast_value_create_string(var_str ? var_str : "");
        }
    }
}
