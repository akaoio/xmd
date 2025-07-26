/**
 * @file xmd_internal_config_new.c
 * @brief Configuration creation function
 * @author XMD Team
 *
 * Implementation of configuration creation for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Create a new configuration with default values
 * @return New configuration instance or NULL on failure
 */
xmd_internal_config* xmd_internal_config_new(void) {
    xmd_internal_config* config = malloc(sizeof(xmd_internal_config));
    if (!config) {
        return NULL;
    }
    
    config->limits = create_default_limits();
    config->buffers = create_default_buffers();
    config->paths = create_default_paths();
    config->security = create_default_security();
    config->timing = create_default_timing();
    config->precision = create_default_precision();
    config->config_file_path = NULL;
    
    return config;
}