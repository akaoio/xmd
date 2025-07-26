/**
 * @file resource_limiter_free.c
 * @brief Free a resource limiter
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Free a resource limiter
 * @param limiter Resource limiter to free
 */
void resource_limiter_free(ResourceLimiter* limiter) {
    if (!limiter) {
        return;
    }
    
    free(limiter->last_error);
    free(limiter);
}