/**
 * @file limiter.c
 * @brief Resource limiter implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/resource.h>
#include "../../../include/resource.h"
#include "../../../include/config.h"

/**
 * @brief Resource limiter context structure
 */
struct resource_limiter {
    long max_memory_mb;         /**< Maximum memory in MB */
    long max_cpu_time_ms;       /**< Maximum CPU time in milliseconds */
    long max_execution_time_ms; /**< Maximum execution time in milliseconds */
    char* last_error;           /**< Last error message */
};

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

/**
 * @brief Free a resource limiter
 * @param limiter Resource limiter to free
 */
void resource_limiter_free(ResourceLimiter* limiter) {
    if (!limiter) {
        return;
    }
    
    free(limiter->last_error);
    free(limiter);
}

/**
 * @brief Set error message in limiter
 * @param limiter Resource limiter
 * @param message Error message
 */
static void set_limiter_error(ResourceLimiter* limiter, const char* message) {
    if (!limiter || !message) {
        return;
    }
    
    free(limiter->last_error);
    limiter->last_error = strdup(message);
}

/**
 * @brief Set memory limit
 * @param limiter Resource limiter
 * @param max_memory_mb Maximum memory in MB
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb) {
    if (!limiter) {
        return RESOURCE_ERROR;
    }
    
    if (max_memory_mb <= 0) {
        set_limiter_error(limiter, "Invalid memory limit");
        return RESOURCE_ERROR;
    }
    
    limiter->max_memory_mb = max_memory_mb;
    return RESOURCE_SUCCESS;
}

/**
 * @brief Set CPU time limit
 * @param limiter Resource limiter
 * @param max_cpu_time_ms Maximum CPU time in milliseconds
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms) {
    if (!limiter) {
        return RESOURCE_ERROR;
    }
    
    if (max_cpu_time_ms <= 0) {
        set_limiter_error(limiter, "Invalid CPU time limit");
        return RESOURCE_ERROR;
    }
    
    limiter->max_cpu_time_ms = max_cpu_time_ms;
    return RESOURCE_SUCCESS;
}

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