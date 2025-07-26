/**
 * @file xmd_internal_config_get_global.c
 * @brief Global configuration getter function
 * @author XMD Team
 *
 * Implementation of global configuration access for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Get global configuration instance
 * @return Global configuration instance
 */
xmd_internal_config* xmd_internal_config_get_global(void) {
    if (!g_config) {
        g_config = xmd_internal_config_new();
        if (g_config) {
            xmd_internal_config_load_env(g_config);
        }
    }
    return g_config;
}