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
    
    // Free sandbox config if present
    if (config->sandbox) {
        free(config->sandbox);
    }
    
    // Free module search paths
    if (config->module_search_paths) {
        for (size_t i = 0; i < config->search_path_count; i++) {
            free(config->module_search_paths[i]);
        }
        free(config->module_search_paths);
    }
    
    // Free output format string
    free(config->output_format);
    
    free(config);
}