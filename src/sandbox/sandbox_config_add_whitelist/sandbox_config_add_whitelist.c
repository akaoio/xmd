/**
 * @file sandbox_config_add_whitelist.c
 * @brief Add command to whitelist
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Add command to whitelist
 * @param config Sandbox configuration
 * @param command Command to whitelist
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_whitelist(SandboxConfig* config, const char* command) {
    if (!config || !command) return SANDBOX_ERROR;
    
    // Reallocate whitelist array
    char** new_whitelist = realloc(config->command_whitelist, 
                                   (config->whitelist_count + 1) * sizeof(char*));
    if (!new_whitelist) return SANDBOX_ERROR;
    
    config->command_whitelist = new_whitelist;
    config->command_whitelist[config->whitelist_count] = strdup(command);
    if (!config->command_whitelist[config->whitelist_count]) return SANDBOX_ERROR;
    
    config->whitelist_count++;
    return SANDBOX_SUCCESS;
}