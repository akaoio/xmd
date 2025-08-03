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
#include "utils/common/common_macros.h"

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
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FUNCTION_CALL, NULL, "ast_evaluate_function_call: Invalid node type");
    
    // Validate function name
    if (!node->data.function_call.name || strlen(node->data.function_call.name) == 0) {
        XMD_ERROR_RETURN(NULL, "ast_evaluate_function_call: Empty or NULL function name");
    }
    
    // Handle built-in print function
    if (strcmp(node->data.function_call.name, "print") == 0) {
        if (node->data.function_call.argument_count > 0) {
            // Evaluate the argument to print
            ast_value* arg_value = ast_evaluate(node->data.function_call.arguments[0], evaluator);
            if (arg_value) {
                char* output = ast_value_to_string(arg_value);
                if (output) {
                    // Interpolate variables in the output string
                    char* interpolated = ast_interpolate_string(output, evaluator);
                    // Append to evaluator's output buffer
                    ast_evaluator_append_output(evaluator, interpolated);
                    ast_evaluator_append_output(evaluator, "\n");
                    XMD_FREE_SAFE(interpolated);
                    XMD_FREE_SAFE(output);
                }
                XMD_FREE_SAFE(arg_value);
            }
        }
        // Print function returns empty string (no return value)
        return ast_value_create_string("");
    }
    
    // Look up user-defined function in evaluator's functions store
    if (!evaluator->functions) {
        XMD_ERROR_RETURN(NULL, "ast_evaluate_function_call: No functions store available for function '%s'", node->data.function_call.name);
    }
    
    // Extract function name without parentheses for lookup
    char func_name_clean[256];
    const char* paren = strchr(node->data.function_call.name, '(');
    if (paren) {
        size_t name_len = paren - node->data.function_call.name;
        if (name_len < sizeof(func_name_clean)) {
            strncpy(func_name_clean, node->data.function_call.name, name_len);
            func_name_clean[name_len] = '\0';
        } else {
            strncpy(func_name_clean, node->data.function_call.name, sizeof(func_name_clean) - 1);
            func_name_clean[sizeof(func_name_clean) - 1] = '\0';
        }
    } else {
        strncpy(func_name_clean, node->data.function_call.name, sizeof(func_name_clean) - 1);
        func_name_clean[sizeof(func_name_clean) - 1] = '\0';
    }
    
    // fprintf(stderr, "DEBUG: Looking for function '%s' with %zu arguments\n", func_name_clean, node->data.function_call.argument_count);
    variable* func_var = store_get(evaluator->functions, func_name_clean);
    if (!func_var) {
        // Debug: List all functions in store
        size_t count = 0;
        char** keys = store_keys(evaluator->functions, &count);
        if (keys) {
            fprintf(stderr, "DEBUG: Available functions in store (%zu total):\n", count);
            for (size_t i = 0; i < count; i++) {
                fprintf(stderr, "  - '%s'\n", keys[i]);
                XMD_FREE_SAFE(keys[i]);
            }
            XMD_FREE_SAFE(keys);
        }
        XMD_ERROR_RETURN(NULL, "ast_evaluate_function_call: Function '%s' not defined", func_name_clean);
    }
    
    // Get function definition AST node from stored variable
    ast_node* func_def = (ast_node*)func_var->value.object_value; // Get AST node pointer from NULL-type variable
    // Check parameter count matches
    if (node->data.function_call.argument_count != func_def->data.function_def.parameter_count) {
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
                // fprintf(stderr, "DEBUG: Binding parameter '%s' to value\n", param_name);
                store_set(evaluator->variables, param_name, param_var);
                variable_unref(param_var);
            }
            XMD_FREE_SAFE(arg_value);
        }
    }
    
    ast_value* result = NULL;
    // Execute function body if it exists
    if (func_def->data.function_def.body) {
        result = ast_evaluate(func_def->data.function_def.body, evaluator);
    } else {
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
    
    XMD_FREE_SAFE(backup_vars);
    return result ? result : ast_value_create_string("");
}
