/**
 * @file process_set.c
 * @brief Process set directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

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
    char* assignment = strdup(args);
    char* equals = strchr(assignment, '=');
    
    if (equals) {
        *equals = '\0';
        char* var_name = trim_whitespace(assignment);
        char* var_value = trim_whitespace(equals + 1);
        
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
    
    free(assignment);
    output[0] = '\0';
    return 0;
}
