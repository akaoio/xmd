/**
 * @file catch_block_begin.c
 * @brief Catch block initialization function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief Begin a catch block
 * @param ctx Error context
 * @param error_type Type of error to catch
 * @return 0 on success, non-zero on error
 */
int catch_block_begin(ErrorContext* ctx, ErrorType error_type) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_catch_block = 1;
    ctx->catch_type = error_type;
    
    // Check if we have a matching error
    if (ctx->current_error && ctx->current_error->type == error_type) {
        ctx->error_caught = 1;
    }
    
    return 0;
}