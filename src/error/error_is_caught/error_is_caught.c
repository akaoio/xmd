/**
 * @file error_is_caught.c
 * @brief Error caught status check function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/error.h"

/**
 * @brief Check if error is caught
 * @param ctx Error context
 * @return 1 if caught, 0 if not
 */
int error_is_caught(ErrorContext* ctx) {
    if (!ctx) {
        return 0;
    }
    
    return ctx->error_caught;
}