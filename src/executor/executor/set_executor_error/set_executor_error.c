/**
 * @file set_executor_error.c
 * @brief Set error message in context
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Set error message in context
 * @param ctx Executor context
 * @param message Error message
 */
void set_executor_error(ExecutorContext* ctx, const char* message) {
    if (!ctx || !message) {
        return;
    }
    
    free(ctx->last_error);
    ctx->last_error = strdup(message);
}