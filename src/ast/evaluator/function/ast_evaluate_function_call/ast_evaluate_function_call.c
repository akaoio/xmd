/**
 * @file ast_evaluate_function_call.c
 *
 *
 * @brief Implementation of ast_evaluate_function_call function
 * 
 * This file contains ONLY the ast_evaluate_function_call function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "variable.h"
#include "utils.h"

// Forward declaration for output append function
int ast_evaluator_append_output(ast_evaluator* evaluator, const char* text);
// Forward declaration for string interpolation
char* ast_interpolate_string(const char* str, ast_evaluator* evaluator);

/**
 * @brief Evaluate function call node
 * @param node Function call AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_function_call(ast_node* node, ast_evaluator* evaluator) {
    if (!node || node->type != AST_FUNCTION_CALL || !evaluator) {
        return NULL;
    }
    
    printf("DEBUG: Evaluating function call: %s\n", node->data.function_call.name);
    // Handle built-in print function
    if (strcmp(node->data.function_call.name, "print") == 0) {
        if (node->data.function_call.argument_count > 0) {
            // Evaluate the argument to print
            ast_value* arg_value = ast_evaluate(node->data.function_call.arguments[0], evaluator);
            if (arg_value) {
                char* output = ast_value_to_string(arg_value);
                if (output) {
                    printf("DEBUG: Print output before interpolation: '%s'\n", output);
                    // Interpolate variables in the output string
                    char* interpolated = ast_interpolate_string(output, evaluator);
                    printf("DEBUG: Print output after interpolation: '%s'\n", interpolated);
                    // Append to evaluator's output buffer
                    ast_evaluator_append_output(evaluator, interpolated);
                    ast_evaluator_append_output(evaluator, "\n");
                    free(interpolated);
                    free(output);
                }
                ast_value_free(arg_value);
            }
        }
        // Print function returns empty string (no return value)
        return ast_value_create_string("");
    }
    
    // Look up user-defined function in global functions store
    if (!global_functions) {
        printf("DEBUG: No functions store available\n");
        return ast_value_create_string("");
    }
    
    variable* func_var = store_get(global_functions, node->data.function_call.name);
    if (!func_var) {
        printf("DEBUG: Function '%s' not found\n", node->data.function_call.name);
        return ast_value_create_string("");
    }
    
    // Get function definition AST node from stored variable
    ast_node* func_def = (ast_node*)func_var->value.string_value; // Get AST node pointer
    printf("DEBUG: Calling user-defined function '%s' with %zu parameters\n", 
           node->data.function_call.name, node->data.function_call.argument_count);
    // Check parameter count matches
    if (node->data.function_call.argument_count != func_def->data.function_def.parameter_count) {
        printf("DEBUG: Parameter count mismatch: expected %zu, got %zu\n",
               func_def->data.function_def.parameter_count,
               node->data.function_call.argument_count);
        return ast_value_create_string("");
    }
    
    // Backup current variable values that might be overwritten
    variable** backup_vars = xmd_malloc(sizeof(variable*) * func_def->data.function_def.parameter_count);
    if (!backup_vars) {
        return ast_value_create_string("");
    }
    
    // Bind parameters to arguments
    for (size_t i = 0; i < func_def->data.function_def.parameter_count; i++) {
        const char* param_name = func_def->data.function_def.parameters[i];
        
        // Backup existing variable value (if any)
        backup_vars[i] = store_get(evaluator->variables, param_name);
        if (backup_vars[i]) {
            variable_ref(backup_vars[i]); // Add reference so it doesn't get freed
        }
        
        // Evaluate argument and bind to parameter
        ast_value* arg_value = ast_evaluate(node->data.function_call.arguments[i], evaluator);
        if (arg_value) {
            variable* param_var = ast_value_to_variable(arg_value);
            if (param_var) {
                store_set(evaluator->variables, param_name, param_var);
                variable_unref(param_var);
            }
            ast_value_free(arg_value);
        }
    }
    
    printf("DEBUG: Parameters bound successfully\n");
    ast_value* result = NULL;
    // Execute function body if it exists
    if (func_def->data.function_def.body) {
        printf("DEBUG: Executing function body\n");
        result = ast_evaluate(func_def->data.function_def.body, evaluator);
    } else {
        printf("DEBUG: No function body - returning empty result\n");
        result = ast_value_create_string("");
    }
    
    // Restore original variable values
    for (size_t i = 0; i < func_def->data.function_def.parameter_count; i++) {
        const char* param_name = func_def->data.function_def.parameters[i];
        if (backup_vars[i]) {
            // Restore original value
            store_set(evaluator->variables, param_name, backup_vars[i]);
            variable_unref(backup_vars[i]); // Release our reference
        } else {
            // Remove parameter variable if it didn't exist before
            store_remove(evaluator->variables, param_name);
        }
    }
    
    free(backup_vars);
    return result ? result : ast_value_create_string("");
}
