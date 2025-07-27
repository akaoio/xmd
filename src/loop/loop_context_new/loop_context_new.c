/**
 * @file loop_context_new.c
 * @brief Loop context creation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/loop.h"

/**
 * @brief Create a new loop context
 * @return New loop context or NULL on error
 */
LoopContext* loop_context_new(void) {
    LoopContext* ctx = malloc(sizeof(LoopContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->break_requested = 0;
    ctx->continue_requested = 0;
    ctx->max_iterations = 1000; // Safety limit
    ctx->last_error = NULL;
    
    return ctx;
}