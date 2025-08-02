/**
 * @file xmd_internal_config_get_global.c
 * @brief Get global internal configuration instance
 * 
 * This file contains ONLY the xmd_internal_config_get_global function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"

// Global configuration instance
static xmd_internal_config* global_config = NULL;

/**
 * @brief Get global internal configuration instance
 * @return Global configuration instance or NULL if not initialized
 */
xmd_internal_config* xmd_internal_config_get_global(void) {
    return global_config;
}

/**
 * @brief Set global internal configuration instance
 * @param config Configuration to set as global
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_set_global(xmd_internal_config* config) {
    global_config = config;
    return 0;
}