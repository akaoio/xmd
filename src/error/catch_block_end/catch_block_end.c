/**
 * @file catch_block_end.c
 * @brief Catch block termination function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief End a catch block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int catch_block_end(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_catch_block = 0;
    ctx->catch_type = ERROR_NONE;
    
    return 0;
}