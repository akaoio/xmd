/**
 * @file create_default_limits.c
 * @brief Implementation of create_default_limits function
 * 
 * This file contains ONLY the create_default_limits function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create default limits configuration
 * @return Default limits configuration or NULL on error
 */
limits_config* create_default_limits(void) {
    limits_config* limits;
    XMD_CALLOC_STANDARD(limits, 1, sizeof(limits_config), NULL);
    
    // Set default limits
    limits->max_memory = 100 * 1024 * 1024;  // 100MB
    limits->max_file_size = 10 * 1024 * 1024;  // 10MB
    limits->max_execution_time = 30;  // 30 seconds
    limits->max_recursion_depth = 100;
    limits->max_variables = 10000;
    limits->max_function_calls = 1000;
    
    return limits;
}