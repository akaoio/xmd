/**
 * @file module_registry_add_search_path.c
 * @brief Module registry search path addition function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Add search path to registry
 * @param registry Module registry
 * @param path Search path to add
 * @return ModuleResult indicating success/failure
 */
int module_registry_add_search_path(ModuleRegistry* registry, const char* path) {
    if (!registry || !path) {
        return MODULE_ERROR;
    }
    
    // Reallocate search paths array
    char** new_paths = realloc(registry->search_paths, 
                              (registry->search_path_count + 1) * sizeof(char*));
    if (!new_paths) {
        return MODULE_ERROR;
    }
    
    registry->search_paths = new_paths;
    registry->search_paths[registry->search_path_count] = strdup(path);
    
    if (!registry->search_paths[registry->search_path_count]) {
        return MODULE_ERROR;
    }
    
    registry->search_path_count++;
    return MODULE_SUCCESS;
}