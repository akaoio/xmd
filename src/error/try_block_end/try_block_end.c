/**
 * @file try_block_end.c
 * @brief Try block termination function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief End a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_end(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_try_block = 0;
    
    return 0;
}