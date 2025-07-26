/**
 * @file create_context.c
 * @brief Create processor context implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Create processor context
 * @param variables Variable store to associate with context
 * @return New processor context (caller must free) or NULL on error
 */
processor_context* create_context(store* variables) {
    processor_context* ctx = malloc(sizeof(processor_context));
    if (!ctx) return NULL;
    
    ctx->variables = variables;
    ctx->if_stack_size = 0;
    ctx->loop_depth = 0;
    ctx->total_iterations = 0;
    ctx->currently_executing = true;
    return ctx;
}
