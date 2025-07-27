/**
 * @file should_execute_block.c
 * @brief Check if current block should execute implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Check if we should execute current block
 * @param ctx Processor context containing execution state
 * @return true if block should execute, false otherwise
 */
bool should_execute_block(processor_context* ctx) {
    if (ctx->if_stack_size == 0) return true;
    
    for (int i = 0; i < ctx->if_stack_size; i++) {
        if (!ctx->if_stack[i].condition_met) {
            return false;
        }
    }
    return true;
}
