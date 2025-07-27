/**
 * @file error_clear.c
 * @brief Error clearing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/error.h"

/**
 * @brief Clear current error
 * @param ctx Error context
 */
void error_clear(ErrorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free_xmd_error(ctx->current_error);
    ctx->current_error = NULL;
    ctx->error_caught = 0;
}