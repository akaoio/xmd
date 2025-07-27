/**
 * @file process_endif.c
 * @brief Process endif directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process endif directive
 * @param ctx Processor context
 * @param output Buffer to store output (unused for endif)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_endif(processor_context* ctx, char* output, size_t output_size) {
    (void)output_size; // Unused parameter
    if (ctx->if_stack_size > 0) {
        ctx->if_stack_size--;
    }
    output[0] = '\0';
    return 0;
}
