/**
 * @file error_context_free.c
 * @brief Error context cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/error.h"

/**
 * @brief Free an error context
 * @param ctx Error context to free
 */
void error_context_free(ErrorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free_xmd_error(ctx->current_error);
    free(ctx);
}