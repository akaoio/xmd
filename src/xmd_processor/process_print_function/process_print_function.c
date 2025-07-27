/**
 * @file process_print_function.c
 * @brief Process print function implementation
 * @author XMD Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process print function call (e.g., print(variable))
 * @param function_call Complete function call string (e.g., "print(mytree)")
 * @param ctx Processor context
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_print_function(const char* function_call, processor_context* ctx, char* output, size_t output_size) {
    // Check if we should execute this block
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Parse print(variable_name)
    const char* start = strchr(function_call, '(');
    const char* end = strrchr(function_call, ')');
    
    if (!start || !end || start >= end) {
        snprintf(output, output_size, "[Error: Invalid print() syntax]");
        return -1;
    }
    
    // Extract variable name
    size_t var_name_len = end - start - 1;
    char* var_name = malloc(var_name_len + 1);
    strncpy(var_name, start + 1, var_name_len);
    var_name[var_name_len] = '\0';
    
    // Trim whitespace from variable name
    char* trimmed_name = trim_whitespace(var_name);
    
    // Get variable value
    variable* var = store_get(ctx->variables, trimmed_name);
    if (var) {
        const char* var_value = variable_to_string(var);
        if (var_value) {
            snprintf(output, output_size, "%s", var_value);
        } else {
            output[0] = '\0';
        }
    } else {
        snprintf(output, output_size, "[Error: Variable '%s' not found]", trimmed_name);
        free(var_name);
        return -1;
    }
    
    free(var_name);
    return 0;
}