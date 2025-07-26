/**
 * @file process_exec.c
 * @brief Process exec directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

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
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Substitute variables in command
    char* expanded = substitute_variables(args, ctx->variables);
    int result = execute_command(expanded, output, output_size);
    free(expanded);
    return result;
}
