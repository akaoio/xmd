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
/**
 * @brief Evaluate identifier node
 * @param node Identifier AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_identifier(ast_node* node, ast_evaluator* evaluator) {
    if (!node || node->type != AST_IDENTIFIER || !evaluator) {
        return NULL;
    }
    
    const char* var_name = node->data.identifier.name;
    printf("DEBUG: Looking up variable '%s' in evaluator\n", var_name);
    variable* var = store_get(evaluator->variables, var_name);
    if (!var) {
        printf("DEBUG: Variable '%s' not found in evaluator store\n", var_name);
        return ast_value_create_string(""); // Return empty string for undefined variables
    }
    
    printf("DEBUG: Found variable '%s' with type %d\n", var_name, variable_get_type(var));
    // Convert variable to AST value based on its actual type
    variable_type var_type = variable_get_type(var);
    switch (var_type) {
        case VAR_STRING: {
            const char* str_val = variable_get_string(var);
            printf("DEBUG: Variable '%s' string value: '%s'\n", var_name, str_val ? str_val : "NULL");
            return ast_value_create_string(str_val ? str_val : "");
        }
        case VAR_NUMBER: {
            double num_val = variable_get_number(var);
            printf("DEBUG: Variable '%s' number value: %f\n", var_name, num_val);
            return ast_value_create_number(num_val);
        }
        case VAR_BOOLEAN: {
            bool bool_val = variable_get_boolean(var);
            printf("DEBUG: Variable '%s' boolean value: %s\n", var_name, bool_val ? "true" : "false");
            return ast_value_create_boolean(bool_val);
        }
        case VAR_ARRAY:
        case VAR_OBJECT: {
            // Handle array by converting all elements to a comma-separated string
            printf("DEBUG: Variable '%s' is array/object type %d\n", var_name, var_type);
            
            // For now, use variable_to_string to get some representation
            const char* var_str = variable_to_string(var);
            if (var_str) {
                printf("DEBUG: Array/object string representation: '%s'\n", var_str);
                return ast_value_create_string(var_str);
            }
            // If variable_to_string doesn't work well for arrays, we'll need to
            // implement proper array-to-string conversion here
            return ast_value_create_string("[array]");
        }
        default: {
            // Fallback to string conversion
            const char* var_str = variable_to_string(var);
            printf("DEBUG: Variable '%s' fallback string: '%s'\n", var_name, var_str ? var_str : "NULL");
            return ast_value_create_string(var_str ? var_str : "");
        }
    }
}
