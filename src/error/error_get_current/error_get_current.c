/**
 * @file error_get_current.c
 * @brief Current error retrieval function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief Get current error
 * @param ctx Error context
 * @return Current error or NULL if none
 */
XMDError* error_get_current(ErrorContext* ctx) {
    if (!ctx) {
        return NULL;
    }
    
    return ctx->current_error;
}