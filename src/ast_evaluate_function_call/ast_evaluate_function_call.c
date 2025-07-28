/**
 * @file ast_evaluate_function_call.c
 * @brief Evaluate function call
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Evaluate function call
 * @param node Function call AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_function_call(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator || node->type != AST_FUNCTION_CALL) {
        return NULL;
    }
    
    const char* func_name = node->data.function_call.name;
    
    // Handle import function
    if (strcmp(func_name, "import") == 0) {
        if (node->data.function_call.argument_count < 1) {
            return NULL;
        }
        
        ast_value* filename_val = ast_evaluate(node->data.function_call.arguments[0], evaluator);
        if (!filename_val || filename_val->type != AST_VAL_STRING) {
            ast_value_free(filename_val);
            return NULL;
        }
        
        // Call existing import functionality
        char import_output[65536] = {0};
        int result = process_import(filename_val->value.string_value, evaluator->ctx, import_output, sizeof(import_output));
        
        ast_value_free(filename_val);
        
        if (result == 0) {
            ast_value* value = ast_value_create(AST_VAL_STRING);
            if (value) {
                value->value.string_value = strdup(import_output);
            }
            return value;
        }
        return NULL;
    }
    
    // Handle exec function
    if (strcmp(func_name, "exec") == 0) {
        if (node->data.function_call.argument_count < 1) {
            return NULL;
        }
        
        ast_value* command_val = ast_evaluate(node->data.function_call.arguments[0], evaluator);
        if (!command_val || command_val->type != AST_VAL_STRING) {
            ast_value_free(command_val);
            return NULL;
        }
        
        // Execute command and get output
        char* command_output = execute_command_dynamic(command_val->value.string_value, NULL);
        ast_value_free(command_val);
        
        if (command_output) {
            // Remove trailing newline if present
            size_t len = strlen(command_output);
            if (len > 0 && command_output[len-1] == '\n') {
                command_output[len-1] = '\0';
            }
            
            ast_value* value = ast_value_create(AST_VAL_STRING);
            if (value) {
                value->value.string_value = strdup(command_output);
            }
            free(command_output);
            return value;
        }
        return NULL;
    }
    
    // Unknown function
    return NULL;
}