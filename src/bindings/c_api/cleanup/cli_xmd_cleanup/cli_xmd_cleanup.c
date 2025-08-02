/**
 * @file cli_xmd_cleanup.c
 * @brief Cleanup XMD CLI resources
 * 
 * This file contains ONLY the cli_xmd_cleanup function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/config_internal.h"
#include "utils/common/common_macros.h"

/**
 * @brief Cleanup XMD CLI resources and global state
 * @return XMD_SUCCESS on successful cleanup
 */
xmd_error_code cli_xmd_cleanup(void) {
    // Get global config if available
    xmd_internal_config* global_config = xmd_internal_config_get_global();
    
    // Free global configuration if it exists
    if (global_config) {
        xmd_internal_config_XMD_FREE_SAFE(global_config);
        xmd_internal_config_set_global(NULL);
    }
    
    // Additional cleanup can be added here for:
    // - Memory pools
    // - File handles
    // - Network connections
    // - Cache cleanup
    
    return XMD_SUCCESS;
}