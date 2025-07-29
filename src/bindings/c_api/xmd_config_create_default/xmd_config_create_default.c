/**
 * @file xmd_config_create_default.c
 * @brief XMD default configuration creator
 * @author XMD Team
 *
 * Implementation of XMD default configuration creation for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Create default XMD configuration
 * @return Default configuration structure
 */
xmd_config* c_api_xmd_config_create_default(void) {
    return config_create();
}
