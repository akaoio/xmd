/**
 * @file resource_limiter_set_cpu_limit.c
 * @brief Set CPU time limit
 */

#include "../../../../include/resource.h"
#include "utils/common/common_macros.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms) {
    XMD_VALIDATE_PTRS(-1, limiter);
    limiter->max_cpu_time_ms = max_cpu_time_ms;
    return 0;
}
