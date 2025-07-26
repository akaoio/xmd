/**
 * @file process_xmd_directive.c
 * @brief Process XMD directive (backward compatibility) implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Process XMD directive (for backward compatibility)
 * @param directive The directive string to process
 * @param var_store Variable store for processing
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size) {
    processor_context ctx = { .variables = var_store, .if_stack_size = 0, .currently_executing = true };
    return process_directive(directive, &ctx, output, output_size);
}
