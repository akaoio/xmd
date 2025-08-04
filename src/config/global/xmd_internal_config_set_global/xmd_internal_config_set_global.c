/**
 * @file xmd_internal_config_set_global.c
 * @brief Implementation of xmd_internal_config_set_global function
 * 
 * This file contains ONLY the xmd_internal_config_set_global function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config_internal.h"
#include "../../../utils/common/validation_macros.h"

// Forward declaration
void config_set_global(xmd_internal_config* config);

/**
 * @brief Set global XMD configuration instance
 * @param config Configuration to set as global (can be NULL to clear)
 */
void xmd_internal_config_set_global(xmd_internal_config* config) {
    // Delegate to the actual implementation
    config_set_global(config);
}