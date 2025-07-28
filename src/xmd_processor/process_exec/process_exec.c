/**
 * @file process_exec.c
 * @brief Process exec directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process exec directive
 * @param args Arguments for exec directive
 * @param ctx Processor context
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_exec(const char* args, processor_context* ctx, char* output, size_t output_size) {
    // Rule 13: Error handling - validate inputs
    if (!args || !ctx || !output || output_size == 0) {
        if (output && output_size > 0) {
            output[0] = '\0';
        }
        return -1;
    }
    
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Substitute variables in command
    char* expanded = substitute_variables(args, ctx->variables);
    if (!expanded) {
        output[0] = '\0';
        return -1;
    }
    
    // Check sandbox permissions before executing command
    if (ctx->sandbox_ctx && !sandbox_check_command_allowed(ctx->sandbox_ctx, expanded)) {
        snprintf(output, output_size, "[Error: Command blocked by sandbox security policy]");
        free(expanded);
        return -1;
    }
    
    int result = execute_command(expanded, output, output_size);
    free(expanded);
    return result;
}

/**
 * @brief Process exec directive with dynamic output allocation
 * @param args Arguments for exec directive
 * @param ctx Processor context
 * @return Dynamically allocated output string (caller must free) or NULL on error
 */
char* process_exec_dynamic(const char* args, processor_context* ctx) {
    // Rule 13: Error handling - validate inputs
    if (!args || !ctx) {
        return NULL;
    }
    
    if (!should_execute_block(ctx)) {
        return strdup("");  // Return empty string for consistency
    }
    
    // Substitute variables in command
    char* expanded = substitute_variables(args, ctx->variables);
    if (!expanded) {
        return NULL;
    }
    
    // Check sandbox permissions before executing command
    if (ctx->sandbox_ctx && !sandbox_check_command_allowed(ctx->sandbox_ctx, expanded)) {
        free(expanded);
        return strdup("[Error: Command blocked by sandbox security policy]");
    }
    
    char* result = execute_command_dynamic(expanded, NULL);
    free(expanded);
    return result;
}
