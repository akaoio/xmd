/**
 * @file executor_context_free.c
 * @brief Free an executor context
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Free an executor context
 * @param ctx Executor context to free
 */
void executor_context_free(ExecutorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx->last_error);
    free(ctx);
}