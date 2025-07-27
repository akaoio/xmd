/**
 * @file module_resolve_path.c
 * @brief Module path resolution function
 * @author XMD Team
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/module_internal.h"

/**
 * @brief Resolve module path
 * @param registry Module registry
 * @param name Module name or relative path
 * @param resolved_path Buffer to store resolved path (caller must free)
 * @return ModuleResult indicating success/failure
 */
int module_resolve_path(ModuleRegistry* registry, const char* name, char** resolved_path) {
    if (!registry || !name || !resolved_path) {
        return MODULE_ERROR;
    }
    
    *resolved_path = NULL;
    
    // If it's an absolute path, use it directly
    if (name[0] == '/') {
        if (file_exists(name)) {
            *resolved_path = strdup(name);
            return *resolved_path ? MODULE_SUCCESS : MODULE_ERROR;
        }
        return MODULE_NOT_FOUND;
    }
    
    // Try to find in search paths
    for (size_t i = 0; i < registry->search_path_count; i++) {
        size_t path_len = strlen(registry->search_paths[i]) + strlen(name) + 10;
        char* candidate = malloc(path_len);
        if (!candidate) {
            return MODULE_ERROR;
        }
        
        // Try with .xmd extension
        snprintf(candidate, path_len, "%s/%s.xmd", registry->search_paths[i], name);
        if (file_exists(candidate)) {
            *resolved_path = candidate;
            return MODULE_SUCCESS;
        }
        
        // Try without extension
        snprintf(candidate, path_len, "%s/%s", registry->search_paths[i], name);
        if (file_exists(candidate)) {
            *resolved_path = candidate;
            return MODULE_SUCCESS;
        }
        
        free(candidate);
    }
    
    // If not found in search paths and it's a relative name, assume it's a path
    if (file_exists(name)) {
        *resolved_path = strdup(name);
        return *resolved_path ? MODULE_SUCCESS : MODULE_ERROR;
    }
    
    return MODULE_NOT_FOUND;
}
