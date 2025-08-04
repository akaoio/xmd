/**
 * @file xmd_internal_config_add_module_path.c
 * @brief Add module search path to configuration
 * 
 * This file contains ONLY the xmd_internal_config_add_module_path function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../../utils/common/common_macros.h"
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
    FOR_EACH_INDEX(i, config->paths.module_search_path_count) {
        if (STR_EQUALS(config->paths.module_search_paths[i], path)) {
            // Path already exists
            return 0;
        }
    }
    
    // Expand the array
    size_t new_count = config->paths.module_search_path_count + 1;
    char** new_paths;
    XMD_REALLOC_VALIDATED(config->paths.module_search_paths, char*, 
                          new_count * sizeof(char*), -1);
    new_paths = config->paths.module_search_paths;
    
    // Add the new path
    XMD_STRDUP_VALIDATED(new_paths[config->paths.module_search_path_count], path, -1);
    
    // Update configuration
    config->paths.module_search_paths = new_paths;
    config->paths.module_search_path_count = new_count;
    
    return 0;
}