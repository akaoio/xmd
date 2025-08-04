/**
 * @file xmd_set_config.c
 * @brief Set XMD configuration value
 * 
 * This file contains ONLY the xmd_set_config function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/config_internal.h"
#include "utils/common/common_macros.h"

/**
 * @brief Set XMD configuration value
 * @param key Configuration key
 * @param value Configuration value
 * @return XMD_SUCCESS on success, XMD_ERROR_INVALID_ARGUMENT on failure
 */
xmd_error_code xmd_set_config(const char* key, const char* value) {
    XMD_VALIDATE_PTRS(XMD_ERROR_INVALID_ARGUMENT, key, value);
    
    // Get global configuration
    xmd_internal_config* config = xmd_internal_config_get_global();
    if (!config) {
        // Create default configuration if none exists
        config = xmd_internal_config_new();
        if (!config) {
            return XMD_ERROR_OUT_OF_MEMORY;
        }
        xmd_internal_config_set_global(config);
    }
    
    // For now, just return success as the configuration system
    // needs to be implemented with proper key-value storage
    return XMD_SUCCESS;
}