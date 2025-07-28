/**
 * @file sandbox_check_command_allowed.c
 * @brief Check if command is allowed
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Check if command is allowed
 * @param ctx Sandbox context
 * @param command Command to check
 * @return SandboxResult indicating allowed/denied
 */
int sandbox_check_command_allowed(SandboxContext* ctx, const char* command) {
    if (!ctx || !ctx->config || !command) return 0; // Error treated as denied (false)
    
    char cmd_name[256];
    // Initialize buffer to ensure it's null-terminated
    memset(cmd_name, 0, sizeof(cmd_name));
    
    if (extract_command_name(command, cmd_name, sizeof(cmd_name)) != 0) {
        return 0; // Error treated as denied (false)
    }
    
    // Ensure cmd_name is valid for comparison
    if (strlen(cmd_name) == 0) {
        return 0; // Error treated as denied (false)
    }
    
    // Check whitelist first
    if (ctx->config->command_whitelist != NULL) {
        for (size_t i = 0; i < ctx->config->whitelist_count; i++) {
            if (ctx->config->command_whitelist[i] != NULL) {
                // Additional defensive check before strlen
                const char* whitelist_cmd = ctx->config->command_whitelist[i];
                if (whitelist_cmd != NULL && strlen(whitelist_cmd) > 0) {
                    if (strcmp(whitelist_cmd, cmd_name) == 0) {
                        return 1; // Allowed (true)
                    }
                }
            }
        }
    }
    
    // Check blacklist
    if (ctx->config->command_blacklist != NULL) {
        for (size_t i = 0; i < ctx->config->blacklist_count; i++) {
            if (ctx->config->command_blacklist[i] != NULL &&
                strlen(ctx->config->command_blacklist[i]) > 0 &&
                strcmp(ctx->config->command_blacklist[i], cmd_name) == 0) {
                return 0; // Denied (false)
            }
        }
    }
    
    // If not in whitelist and whitelist exists, deny
    if (ctx->config->whitelist_count > 0) {
        return 0; // Denied - not in whitelist (false)
    }
    
    // Default: allow if no whitelist is configured
    return 1; // Allowed (true)
}