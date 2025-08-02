/**
 * @file resource_limiter_set_memory_limit.c
 * @brief Set memory limit
 */

#include "../../../../include/resource.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb) {
    if (!limiter) {
        return -1;
    }
    limiter->max_memory_mb = max_memory_mb;
    return 0;
}
