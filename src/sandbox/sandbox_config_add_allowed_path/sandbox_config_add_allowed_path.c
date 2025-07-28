/**
 * @file sandbox_config_add_allowed_path.c
 * @brief Add path to allowed paths
 * @author XMD Team
 */

#define _GNU_SOURCE
#include "../../../include/sandbox_internal.h"

/**
 * @brief Add path to allowed paths
 * @param config Sandbox configuration
 * @param path Path to allow
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_allowed_path(SandboxConfig* config, const char* path) {
    if (!config || !path || strlen(path) == 0) return SANDBOX_ERROR;
    
    // Reallocate allowed paths array
    char** new_paths = realloc(config->allowed_paths, 
                               (config->allowed_path_count + 1) * sizeof(char*));
    if (!new_paths) return SANDBOX_ERROR;
    
    config->allowed_paths = new_paths;
    
    // Use strdup and check for failure
    char* path_copy = strdup(path);
    if (!path_copy) {
        return SANDBOX_ERROR;
    }
    
    config->allowed_paths[config->allowed_path_count] = path_copy;
    config->allowed_path_count++;
    return SANDBOX_SUCCESS;
}