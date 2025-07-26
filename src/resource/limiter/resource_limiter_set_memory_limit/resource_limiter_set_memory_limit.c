/**
 * @file resource_limiter_set_memory_limit.c
 * @brief Set memory limit
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Set memory limit
 * @param limiter Resource limiter
 * @param max_memory_mb Maximum memory in MB
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb) {
    if (!limiter) {
        return RESOURCE_ERROR;
    }
    
    if (max_memory_mb <= 0) {
        set_limiter_error(limiter, "Invalid memory limit");
        return RESOURCE_ERROR;
    }
    
    limiter->max_memory_mb = max_memory_mb;
    return RESOURCE_SUCCESS;
}