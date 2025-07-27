/**
 * @file error_handling.c
 * @brief Error handling implementation
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/error.h"

/**
 * @brief Create a new error context
 * @return New error context or NULL on error
 */
ErrorContext* error_context_new(void) {
    ErrorContext* ctx = malloc(sizeof(ErrorContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->current_error = NULL;
    ctx->in_try_block = 0;
    ctx->in_catch_block = 0;
    ctx->catch_type = ERROR_NONE;
    ctx->error_caught = 0;
    
    return ctx;
}
