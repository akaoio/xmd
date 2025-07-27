/**
 * @file executor_context_new.c
 * @brief Executor context creation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/executor.h"

/**
 * @brief Create a new executor context
 * @return New executor context or NULL on error
 */
ExecutorContext* executor_context_new(void) {
    ExecutorContext* ctx = malloc(sizeof(ExecutorContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->last_error = NULL;
    ctx->timeout_ms = 30000; // 30 second default timeout
    ctx->enable_capture = 1; // Enable output capture by default
    ctx->max_output_size = 10 * 1024 * 1024; // 10MB default max output size
    
    return ctx;
}