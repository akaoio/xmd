/**
 * @file xmd_get_config.c
 * @brief Get XMD configuration value
 * 
 * This file contains ONLY the xmd_get_config function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/config_internal.h"
#include "utils/common/common_macros.h"

/**
 * @brief Get XMD configuration value
 * @param key Configuration key
 * @return Configuration value or NULL if not found
 */
const char* xmd_get_config(const char* key) {
    XMD_VALIDATE_PTRS(NULL, key);
    
    // Get global configuration
    xmd_internal_config* config = xmd_internal_config_get_global();
    if (!config) {
        return NULL;
    }
    
    // Get the configuration value
    return config_get(config, key);
}