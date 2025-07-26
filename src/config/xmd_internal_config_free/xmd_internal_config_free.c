/**
 * @file xmd_internal_config_free.c
 * @brief Free internal configuration function
 * @author XMD Team
 *
 * Implementation of internal configuration cleanup for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Free internal configuration
 * @param config Configuration to free
 */
void xmd_internal_config_free(xmd_internal_config* config) {
    if (!config) {
        return;
    }
    
    free_paths_config(&config->paths);
    free_security_config(&config->security);
    free(config->config_file_path);
    free(config);
}