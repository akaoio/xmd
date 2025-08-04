/**
 * @file create_default_limits.c
 * @brief Implementation of create_default_limits function
 * 
 * This file contains ONLY the create_default_limits function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Create default limits configuration
 * @return Default limits configuration
 */
xmd_resource_limits create_default_limits(void) {
    xmd_resource_limits limits = {0};
    
    // Set default limits
    limits.memory_limit_mb = 100;                 // 100MB
    limits.cpu_time_limit_ms = 30000;            // 30 seconds
    limits.execution_time_limit_ms = 30000;      // 30 seconds  
    limits.max_output_size = 10 * 1024 * 1024;   // 10MB
    limits.max_recursion_depth = 100;
    limits.max_loop_iterations = 1000000;        // 1M iterations
    
    return limits;
}