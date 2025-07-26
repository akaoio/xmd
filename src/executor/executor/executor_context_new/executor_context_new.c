/**
 * @file executor_context_new.c
 * @brief Create a new executor context
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Create a new executor context
 * @return New executor context or NULL on error
 */
ExecutorContext* executor_context_new(void) {
    ExecutorContext* ctx = malloc(sizeof(ExecutorContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->default_timeout_ms = 30000; // 30 seconds default
    ctx->max_output_size = 1024 * 1024; // 1MB max output
    ctx->last_error = NULL;
    
    return ctx;
}