#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file set_limiter_error.c
 * @brief Set error message in limiter
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/limiter_internal.h"

/**
 * @brief Set error message in limiter
 * @param limiter Resource limiter
 * @param message Error message
 */
void set_limiter_error(ResourceLimiter* limiter, const char* message) {
    if (!limiter || !message) {
        return;
    }
    
    free(limiter->last_error);
    limiter->last_error = strdup(message);
}