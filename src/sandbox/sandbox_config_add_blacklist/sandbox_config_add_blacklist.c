/**
 * @file sandbox_config_add_blacklist.c
 * @brief Add command to blacklist
 * @author XMD Team
 */

#define _GNU_SOURCE
#include "../../../include/sandbox_internal.h"

/**
 * @brief Add command to blacklist
 * @param config Sandbox configuration
 * @param command Command to blacklist
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_blacklist(SandboxConfig* config, const char* command) {
    if (!config || !command || strlen(command) == 0) return SANDBOX_ERROR;
    
    // Reallocate blacklist array
    char** new_blacklist = realloc(config->command_blacklist, 
                                   (config->blacklist_count + 1) * sizeof(char*));
    if (!new_blacklist) return SANDBOX_ERROR;
    
    config->command_blacklist = new_blacklist;
    
    // Use strdup and check for failure
    char* cmd_copy = strdup(command);
    if (!cmd_copy) {
        return SANDBOX_ERROR;
    }
    
    config->command_blacklist[config->blacklist_count] = cmd_copy;
    config->blacklist_count++;
    return SANDBOX_SUCCESS;
}