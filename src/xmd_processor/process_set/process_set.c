/**
 * @file process_set.c
 * @brief Process set directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process set directive
 * @param args Arguments for set directive (variable assignment)
 * @param ctx Processor context
 * @param output Buffer to store output (unused for set)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_set(const char* args, processor_context* ctx, char* output, size_t output_size) {
    (void)output_size; // Unused parameter
    
    // Check if we should execute this block
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    char* assignment = strdup(args);
    char* plus_equals = strstr(assignment, "+=");
    
    if (plus_equals) {
        // Handle += operator (string concatenation)
        *plus_equals = '\0';
        char* var_name = trim_whitespace(assignment);
        char* append_value = trim_whitespace(plus_equals + 2);
        
        // Get existing variable
        variable* existing = store_get(ctx->variables, var_name);
        if (existing && existing->type == VAR_STRING) {
            // Check if append_value contains expressions (has + operator outside quotes)
            if (strstr(append_value, " + ")) {
                // This is an expression, need to evaluate it
                // For now, just handle simple quoted strings
                // TODO: Integrate with evaluate_concatenation_expression from process_script_block
                
                // Remove quotes from append value if present
                if (strlen(append_value) >= 2 &&
                    ((append_value[0] == '"' && append_value[strlen(append_value)-1] == '"') ||
                     (append_value[0] == '\'' && append_value[strlen(append_value)-1] == '\''))) {
                    append_value[strlen(append_value)-1] = '\0';
                    append_value++;
                }
                
                // Concatenate strings
                size_t new_len = strlen(existing->value.string_value) + strlen(append_value) + 1;
                char* new_value = malloc(new_len);
                if (new_value) {
                    snprintf(new_value, new_len, "%s%s", existing->value.string_value, append_value);
                    variable* new_var = variable_create_string(new_value);
                    if (new_var) {
                        store_set(ctx->variables, var_name, new_var);
                        variable_unref(new_var);
                    }
                    free(new_value);
                }
            } else {
                // Simple string append
                // Remove quotes from append value if present
                if (strlen(append_value) >= 2 &&
                    ((append_value[0] == '"' && append_value[strlen(append_value)-1] == '"') ||
                     (append_value[0] == '\'' && append_value[strlen(append_value)-1] == '\''))) {
                    append_value[strlen(append_value)-1] = '\0';
                    append_value++;
                }
                
                // Concatenate strings
                size_t new_len = strlen(existing->value.string_value) + strlen(append_value) + 1;
                char* new_value = malloc(new_len);
                if (new_value) {
                    snprintf(new_value, new_len, "%s%s", existing->value.string_value, append_value);
                    variable* new_var = variable_create_string(new_value);
                    if (new_var) {
                        store_set(ctx->variables, var_name, new_var);
                        variable_unref(new_var);
                    }
                    free(new_value);
                }
            }
        }
    } else {
        char* equals = strchr(assignment, '=');
        if (equals) {
        // Handle = operator (assignment)
        *equals = '\0';
        char* var_name = trim_whitespace(assignment);
        char* var_value = trim_whitespace(equals + 1);
        
        // Check for array literal
        if (var_value[0] == '[') {
            variable* array = parse_array_literal(var_value);
            if (array) {
                store_set(ctx->variables, var_name, array);
                variable_unref(array);
            }
        }
        // Check if the value is an exec command
        else if (strncmp(var_value, "exec ", 5) == 0) {
            // Execute the command and store its output
            char* command = trim_whitespace(var_value + 5);
            char* command_output = execute_command_dynamic(command, NULL);
            
            if (command_output) {
                // Remove trailing newline if present
                size_t len = strlen(command_output);
                if (len > 0 && command_output[len-1] == '\n') {
                    command_output[len-1] = '\0';
                }
                
                variable* var = variable_create_string(command_output);
                if (var) {
                    store_set(ctx->variables, var_name, var);
                    variable_unref(var);
                }
                free(command_output);
            }
        } else {
            // Handle regular string assignment
            // Remove quotes if present
            if (strlen(var_value) >= 2 &&
                ((var_value[0] == '"' && var_value[strlen(var_value)-1] == '"') ||
                 (var_value[0] == '\'' && var_value[strlen(var_value)-1] == '\''))) {
                var_value[strlen(var_value)-1] = '\0';
                var_value++;
            }
            
            variable* var = variable_create_string(var_value);
            if (var) {
                store_set(ctx->variables, var_name, var);
                variable_unref(var);
            }
        }
        } else {
            // Variable initialization without assignment (set varname)
            char* var_name = trim_whitespace(assignment);
            variable* var = variable_create_string("");
            if (var) {
                store_set(ctx->variables, var_name, var);
                variable_unref(var);
            }
        }
    }
    
    free(assignment);
    output[0] = '\0';
    return 0;
}
