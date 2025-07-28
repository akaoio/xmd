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
        
        // Substitute variables in command string
        char* substituted_command = ast_substitute_variables(command_val->value.string_value, evaluator->ctx->variables);
        const char* final_command = substituted_command ? substituted_command : command_val->value.string_value;
        
        // Execute command and get output
        char* command_output = execute_command_dynamic(final_command, NULL);
        
        // Clean up substituted command
        if (substituted_command) {
            free(substituted_command);
        }
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
    
    // Handle join function
    if (strcmp(func_name, "join") == 0) {
        if (node->data.function_call.argument_count < 1) {
            return NULL;
        }
        
        ast_value* array_val = ast_evaluate(node->data.function_call.arguments[0], evaluator);
        if (!array_val) {
            return NULL;
        }
        
        // Get separator (default to ", " if not provided)
        const char* separator = ", ";
        ast_value* separator_val = NULL;
        if (node->data.function_call.argument_count >= 2) {
            separator_val = ast_evaluate(node->data.function_call.arguments[1], evaluator);
            if (separator_val && separator_val->type == AST_VAL_STRING) {
                separator = separator_val->value.string_value;
            }
        }
        
        // Handle both array literals and array variables
        if (array_val->type == AST_VAL_ARRAY) {
            size_t separator_len = strlen(separator);
            
            // Calculate total length needed
            size_t total_len = 0;
            for (size_t i = 0; i < array_val->value.array_value.element_count; i++) {
                ast_value* element = array_val->value.array_value.elements[i];
                if (element && element->type == AST_VAL_STRING && element->value.string_value) {
                    total_len += strlen(element->value.string_value);
                    if (i > 0) total_len += separator_len;
                }
            }
            
            // Create result string
            char* result_str = malloc(total_len + 1);
            if (!result_str) {
                ast_value_free(array_val);
                ast_value_free(separator_val);
                return NULL;
            }
            result_str[0] = '\0';
            
            // Join array elements with custom separator
            for (size_t i = 0; i < array_val->value.array_value.element_count; i++) {
                ast_value* element = array_val->value.array_value.elements[i];
                if (element && element->type == AST_VAL_STRING && element->value.string_value) {
                    if (i > 0) {
                        strcat(result_str, separator);
                    }
                    strcat(result_str, element->value.string_value);
                }
            }
            
            ast_value_free(array_val);
            ast_value_free(separator_val);
            
            ast_value* value = ast_value_create(AST_VAL_STRING);
            if (value) {
                value->value.string_value = result_str;
            } else {
                free(result_str);
            }
            return value;
        }
        
        ast_value_free(array_val);
        return NULL;
    }
    
    // Unknown function
    return NULL;
}