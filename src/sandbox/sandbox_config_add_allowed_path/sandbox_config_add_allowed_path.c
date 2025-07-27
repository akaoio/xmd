/**
 * @file sandbox_config_add_allowed_path.c
 * @brief Add path to allowed paths
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Add path to allowed paths
 * @param config Sandbox configuration
 * @param path Path to allow
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_allowed_path(SandboxConfig* config, const char* path) {
    if (!config || !path) return SANDBOX_ERROR;
    
    // Reallocate allowed paths array
    char** new_paths = realloc(config->allowed_paths, 
                               (config->allowed_path_count + 1) * sizeof(char*));
    if (!new_paths) return SANDBOX_ERROR;
    
    config->allowed_paths = new_paths;
    config->allowed_paths[config->allowed_path_count] = strdup(path);
    if (!config->allowed_paths[config->allowed_path_count]) return SANDBOX_ERROR;
    
    config->allowed_path_count++;
    return SANDBOX_SUCCESS;
}