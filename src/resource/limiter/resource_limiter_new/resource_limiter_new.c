/**
 * @file resource_limiter_new.c
 * @brief Create new resource limiter
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/utils.h"
#include "../../../../include/config_internal.h"
ResourceLimiter* resource_limiter_new(void) {
    ResourceLimiter* limiter = xmd_malloc(sizeof(ResourceLimiter));
    if (!limiter) {
        return NULL;
    }
    
    // Get limits from global configuration
    xmd_internal_config* config = xmd_internal_config_get_global();
    if (config) {
        limiter->max_memory_mb = (uint32_t)config->limits.memory_limit_mb;
        limiter->max_cpu_time_ms = (uint32_t)config->limits.cpu_time_limit_ms;
        limiter->max_execution_time_ms = (uint32_t)config->limits.execution_time_limit_ms;
    } else {
        // Default limits if no config
        limiter->max_memory_mb = 100;
        limiter->max_cpu_time_ms = 5000;
        limiter->max_execution_time_ms = 10000;
    }
    limiter->last_error = NULL;
    return limiter;
}
