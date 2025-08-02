/**
 * @file xmd_internal_config_add_module_path.c
 * @brief Add module search path to configuration
 * 
 * This file contains ONLY the xmd_internal_config_add_module_path function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Add module search path to configuration
 * @param config Configuration to modify
 * @param path Module search path to add
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_add_module_path(xmd_internal_config* config, const char* path) {
    XMD_VALIDATE_PTRS(-1, config, path);
    
    // Check if path already exists
    for (size_t i = 0; i < config->paths.module_search_path_count; i++) {
        if (strcmp(config->paths.module_search_paths[i], path) == 0) {
            // Path already exists
            return 0;
        }
    }
    
    // Expand the array
    size_t new_count = config->paths.module_search_path_count + 1;
    char** new_paths = realloc(config->paths.module_search_paths, 
                               new_count * sizeof(char*));
    if (!new_paths) {
        return -1;
    }
    
    // Add the new path
    new_paths[config->paths.module_search_path_count] = strdup(path);
    if (!new_paths[config->paths.module_search_path_count]) {
        return -1;
    }
    
    // Update configuration
    config->paths.module_search_paths = new_paths;
    config->paths.module_search_path_count = new_count;
    
    return 0;
}