/**
 * @file resource_limiter_set_time_limit.c
 * @brief Set execution time limit
 */

#include "../../../../include/resource.h"
#include "../../../utils/common/common_macros.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms) {
    XMD_VALIDATE_PTRS(-1, limiter);
    limiter->max_execution_time_ms = max_execution_time_ms;
    return 0;
}
