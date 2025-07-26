/**
 * @file resource_limiter_check_limits.c
 * @brief Check if resource usage is within limits
 * @author XMD Team
 */

#include "../../../../include/limiter_internal.h"

/**
 * @brief Check if resource usage is within limits
 * @param limiter Resource limiter
 * @param usage Current resource usage
 * @return ResourceResult indicating within limits or exceeded
 */
int resource_limiter_check_limits(ResourceLimiter* limiter, ResourceUsage* usage) {
    if (!limiter || !usage) {
        return RESOURCE_ERROR;
    }
    
    // Check memory limit
    long memory_mb = usage->memory_bytes / (1024 * 1024);
    if (memory_mb > limiter->max_memory_mb) {
        set_limiter_error(limiter, "Memory limit exceeded");
        return RESOURCE_LIMIT_EXCEEDED;
    }
    
    // Check CPU time limit
    if (usage->cpu_time_ms > limiter->max_cpu_time_ms) {
        set_limiter_error(limiter, "CPU time limit exceeded");
        return RESOURCE_LIMIT_EXCEEDED;
    }
    
    // Check execution time limit
    if (usage->execution_time_ms > limiter->max_execution_time_ms) {
        set_limiter_error(limiter, "Execution time limit exceeded");
        return RESOURCE_TIMEOUT;
    }
    
    return RESOURCE_SUCCESS;
}