/**
 * @file sandbox_config_free.c
 * @brief Free a sandbox configuration
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Free a sandbox configuration
 * @param config Configuration to free
 */
void sandbox_config_free(SandboxConfig* config) {
    if (!config) return;
    
    // Free whitelisted commands
    for (size_t i = 0; i < config->whitelist_count; i++) {
        free(config->command_whitelist[i]);
    }
    free(config->command_whitelist);
    
    // Free blacklisted commands  
    for (size_t i = 0; i < config->blacklist_count; i++) {
        free(config->command_blacklist[i]);
    }
    free(config->command_blacklist);
    
    // Free allowed paths
    for (size_t i = 0; i < config->allowed_path_count; i++) {
        free(config->allowed_paths[i]);
    }
    free(config->allowed_paths);
    
    // Free blocked paths
    for (size_t i = 0; i < config->blocked_path_count; i++) {
        free(config->blocked_paths[i]);
    }
    free(config->blocked_paths);
    
    free(config);
}