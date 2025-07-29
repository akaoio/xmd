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
    
    // Initialize configuration with defaults
    config->sandbox = NULL;
    config->max_recursion_depth = 100;
    config->max_loop_iterations = 10000;
    config->cache_max_memory = 64 * 1024 * 1024;
    config->cache_default_ttl_ms = 3600000;
    config->module_search_paths = NULL;
    config->search_path_count = 0;
    config->preserve_comments = false;
    config->pretty_print = false;
    config->output_format = NULL;
    config->debug_mode = false;
    
    return config;
}