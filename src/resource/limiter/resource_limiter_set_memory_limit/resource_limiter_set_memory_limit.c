/**
 * @file resource_limiter_set_memory_limit.c
 * @brief Set memory limit
 */

#include "../../../../include/resource.h"
#include "../../../utils/common/common_macros.h"
/**
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb) {
    XMD_VALIDATE_PTRS(-1, limiter);
    limiter->max_memory_mb = max_memory_mb;
    return 0;
}
