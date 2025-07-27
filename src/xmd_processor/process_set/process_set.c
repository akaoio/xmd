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
    char* equals = strchr(assignment, '=');
    
    if (equals) {
        *equals = '\0';
        char* var_name = trim_whitespace(assignment);
        char* var_value = trim_whitespace(equals + 1);
        
        // Check if the value is an exec command
        if (strncmp(var_value, "exec ", 5) == 0) {
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
    }
    
    free(assignment);
    output[0] = '\0';
    return 0;
}
