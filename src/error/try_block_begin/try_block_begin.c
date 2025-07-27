/**
 * @file try_block_begin.c
 * @brief Try block initialization function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief Begin a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_begin(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_try_block = 1;
    ctx->error_caught = 0;
    
    return 0;
}