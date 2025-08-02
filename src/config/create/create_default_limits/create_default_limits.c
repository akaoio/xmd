/**
 * @file create_default_limits.c
 * @brief Create default resource limits
 * 
 * This file contains ONLY the create_default_limits function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

/**
 * @brief Create default resource limits
 * @return Default resource limits configuration
 */
xmd_resource_limits create_default_limits(void) {
    xmd_resource_limits limits;
    
    // Memory limits
    limits.memory_limit_mb = 64; // 64MB default
    limits.cpu_time_limit_ms = 30000; // 30 seconds CPU time
    limits.execution_time_limit_ms = 30000; // 30 seconds wall time
    limits.max_output_size = 10 * 1024 * 1024; // 10MB output
    limits.max_recursion_depth = 1000; // Stack depth limit
    limits.max_loop_iterations = 100000; // Loop iteration limit
    
    return limits;
}
