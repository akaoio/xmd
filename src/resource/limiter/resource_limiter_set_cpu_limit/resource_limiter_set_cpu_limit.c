/**
 * @file resource_limiter_set_cpu_limit.c
 * @brief Set CPU time limit
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Set CPU time limit
 * @param limiter Resource limiter
 * @param max_cpu_time_ms Maximum CPU time in milliseconds
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms) {
    if (!limiter) {
        return RESOURCE_ERROR;
    }
    
    if (max_cpu_time_ms <= 0) {
        set_limiter_error(limiter, "Invalid CPU time limit");
        return RESOURCE_ERROR;
    }
    
    limiter->max_cpu_time_ms = max_cpu_time_ms;
    return RESOURCE_SUCCESS;
}