/**
 * @file resource_limiter_new.c
 * @brief Create a new resource limiter
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Create a new resource limiter
 * @return New resource limiter or NULL on error
 */
ResourceLimiter* resource_limiter_new(void) {
    ResourceLimiter* limiter = malloc(sizeof(ResourceLimiter));
    if (!limiter) {
        return NULL;
    }
    
    // Get limits from global configuration
    xmd_internal_config* config = xmd_internal_config_get_global();
    limiter->max_memory_mb = (uint32_t)config->limits.memory_limit_mb;
    limiter->max_cpu_time_ms = (uint32_t)config->limits.cpu_time_limit_ms;
    limiter->max_execution_time_ms = (uint32_t)config->limits.execution_time_limit_ms;
    limiter->last_error = NULL;
    
    return limiter;
}