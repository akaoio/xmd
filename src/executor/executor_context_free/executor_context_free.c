/**
 * @file executor_context_free.c
 * @brief Executor context cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/executor.h"

/**
 * @brief Free an executor context
 * @param ctx Executor context to free
 */
void executor_context_free(ExecutorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    if (ctx->last_error) {
        free(ctx->last_error);
    }
    
    free(ctx);
}