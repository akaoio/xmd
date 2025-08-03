/**
 * @file config_create.c
 * @brief Implementation of config_create function
 * 
 * This file contains ONLY the config_create function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/xmd.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create new configuration with default values
 * @return New configuration or NULL on error
 */
xmd_config* config_create(void) {
    xmd_internal_config* config;
    XMD_CALLOC_STANDARD(config, 1, sizeof(xmd_internal_config), NULL);
    
    // Set up default values (temporarily commented out - missing implementations)
    // config->limits = create_default_limits();
    // config->buffers = create_default_buffers();
    // config->paths = create_default_paths();
    // config->precision = create_default_precision();
    // config->security = create_default_security();
    // config->timing = create_default_timing();
    
    // Create default configurations
    config->limits = create_default_limits();
    config->buffers = create_default_buffers();
    config->paths = create_default_paths();
    config->precision = create_default_precision();
    config->security = create_default_security();
    config->timing = create_default_timing();
    
    // Configuration created successfully
    return (xmd_config*)config;
}
