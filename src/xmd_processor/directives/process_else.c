/**
 * @file process_else.c
 * @brief Process else directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process else directive
 * @param ctx Processor context
 * @param output Buffer to store output (unused for else)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_else(processor_context* ctx, char* output, size_t output_size) {
    if (ctx->if_stack_size == 0) {
        snprintf(output, output_size, "[Error: else without if]");
        return -1;
    }
    
    if_stack_entry* entry = &ctx->if_stack[ctx->if_stack_size - 1];
    
    // Only execute else if no previous branch was executed
    entry->condition_met = !entry->branch_executed;
    if (!entry->branch_executed) {
        entry->branch_executed = true;
    }
    
    output[0] = '\0';
    return 0;
}
