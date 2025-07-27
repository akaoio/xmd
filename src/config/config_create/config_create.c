/**
 * @file config_create.c
 * @brief Create configuration structure
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

/**
 * @brief Create configuration structure
 * @return Configuration structure or NULL on error
 */
xmd_config* config_create(void) {
    xmd_config* config = malloc(sizeof(xmd_config));
    if (!config) {
        return NULL;
    }
    
    // Initialize configuration
    config->config_file_path = NULL;
    config->values = NULL;
    config->value_count = 0;
    config->loaded = false;
    
    return config;
}