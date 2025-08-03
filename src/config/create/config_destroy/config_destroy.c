/**
 * @file config_destroy.c
 * @brief Implementation of config_destroy function
 * 
 * This file contains ONLY the config_destroy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/xmd.h"
#include "../../../../include/core_macros.h"
#include <stdlib.h>

/**
 * @brief Free configuration and all associated resources
 * @param config Configuration to free
 */
void config_destroy(xmd_config* config) {
    if (!config) return;
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    XMD_CONFIG_CLEANUP_PATHS(internal);
    XMD_CONFIG_CLEANUP_SECURITY(internal);
    
    XMD_FREE_SAFE(config);
}
