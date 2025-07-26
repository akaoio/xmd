/**
 * @file xmd_internal_config_set_global.c
 * @brief Global configuration setter function
 * @author XMD Team
 *
 * Implementation of global configuration setting for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Set global configuration instance
 * @param config Configuration to set as global
 */
void xmd_internal_config_set_global(xmd_internal_config* config) {
    if (g_config && g_config != config) {
        xmd_internal_config_free(g_config);
    }
    g_config = config;
}