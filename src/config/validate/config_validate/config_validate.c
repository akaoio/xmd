/**
 * @file config_validate.c
 * @brief Validate configuration settings
 * 
 * This file contains ONLY the config_validate function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Validate configuration settings
 * @param config Configuration to validate
 * @return 0 if valid, -1 if invalid
 */
int config_validate(const xmd_internal_config* config) {
    XMD_VALIDATE_PTRS(-1, config);
    
    // Validate resource limits
    if (config->limits.memory_limit_mb == 0 ||
        config->limits.cpu_time_limit_ms == 0 ||
        config->limits.execution_time_limit_ms == 0) {
        return -1;
    }
    
    // Validate buffer configuration
    if (config->buffers.line_buffer_size == 0 ||
        config->buffers.conversion_buffer_size == 0 ||
        config->buffers.initial_store_capacity == 0) {
        return -1;
    }
    
    // Validate load factor
    if (config->buffers.store_load_factor <= 0.0 || 
        config->buffers.store_load_factor >= 1.0) {
        return -1;
    }
    
    // Validate precision configuration
    if (config->precision.float_epsilon <= 0.0 ||
        config->precision.number_format == NULL) {
        return -1;
    }
    
    // All validations passed
    return 0;
}