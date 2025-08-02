/**
 * @file resource_limiter_set_time_limit.c
 * @brief Set execution time limit
 */

#include "../../../../include/resource.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms) {
    if (!limiter) return -1;
    limiter->max_execution_time_ms = max_execution_time_ms;
    return 0;
}
