/**
 * @file xmd_internal_config_add_module_path.c
 * @brief Add module path to configuration function
 * @author XMD Team
 *
 * Implementation of module path addition for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Add module path to configuration
 * @param config Configuration to modify
 * @param path Module path to add
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_add_module_path(xmd_internal_config* config, const char* path) {
    if (!config || !path) {
        return -1;
    }
    
    char** new_paths = realloc(config->paths.module_search_paths,
                              (config->paths.module_search_path_count + 1) * sizeof(char*));
    if (!new_paths) {
        return -1;
    }
    
    config->paths.module_search_paths = new_paths;
    config->paths.module_search_paths[config->paths.module_search_path_count] = strdup(path);
    config->paths.module_search_path_count++;
    
    return 0;
}