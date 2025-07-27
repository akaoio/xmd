/**
 * @file config_destroy.c
 * @brief Configuration cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/cli.h"

/**
 * @brief Destroy configuration structure
 * @param config Configuration structure
 */
void config_destroy(xmd_config* config) {
    if (!config) {
        return;
    }
    
    free(config->config_file_path);
    
    // In a full implementation, we'd free all stored values
    // For now, the simple implementation stores values statically
    
    free(config);
}