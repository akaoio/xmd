/**
 * @file resource_limiter_set_time_limit.c
 * @brief Set execution time limit
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Set execution time limit
 * @param limiter Resource limiter
 * @param max_execution_time_ms Maximum execution time in milliseconds
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms) {
    if (!limiter) {
        return RESOURCE_ERROR;
    }
    
    if (max_execution_time_ms <= 0) {
        set_limiter_error(limiter, "Invalid execution time limit");
        return RESOURCE_ERROR;
    }
    
    limiter->max_execution_time_ms = max_execution_time_ms;
    return RESOURCE_SUCCESS;
}