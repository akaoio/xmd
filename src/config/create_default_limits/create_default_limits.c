/**
 * @file create_default_limits.c
 * @brief Default resource limits creation function
 * @author XMD Team
 *
 * Implementation of default resource limits creation for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Create default resource limits
 * @return Default resource limits configuration
 */
xmd_resource_limits create_default_limits(void) {
    xmd_resource_limits limits = {
        .memory_limit_mb = 100,
        .cpu_time_limit_ms = 5000,
        .execution_time_limit_ms = 10000,
        .max_output_size = 1024 * 1024,  // 1MB
        .max_recursion_depth = 100,
        .max_loop_iterations = 10000
    };
    return limits;
}