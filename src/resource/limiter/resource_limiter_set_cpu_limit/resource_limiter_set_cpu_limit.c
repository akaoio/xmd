/**
 * @file resource_limiter_set_cpu_limit.c
 * @brief Set CPU time limit
 */

#include "../../../../include/resource.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms) {
    if (!limiter) return -1;
    limiter->max_cpu_time_ms = max_cpu_time_ms;
    return 0;
}
