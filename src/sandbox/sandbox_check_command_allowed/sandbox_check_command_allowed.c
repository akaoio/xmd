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
    if (!ctx || !ctx->config || !command) return SANDBOX_ERROR;
    
    char cmd_name[256];
    if (extract_command_name(command, cmd_name, sizeof(cmd_name)) != 0) {
        return SANDBOX_ERROR;
    }
    
    // Check whitelist first
    for (size_t i = 0; i < ctx->config->whitelist_count; i++) {
        if (strcmp(ctx->config->command_whitelist[i], cmd_name) == 0) {
            return SANDBOX_SUCCESS; // Allowed
        }
    }
    
    // Check blacklist
    for (size_t i = 0; i < ctx->config->blacklist_count; i++) {
        if (strcmp(ctx->config->command_blacklist[i], cmd_name) == 0) {
            return SANDBOX_PERMISSION_DENIED; // Denied
        }
    }
    
    // If not in whitelist and whitelist exists, deny
    if (ctx->config->whitelist_count > 0) {
        return SANDBOX_PERMISSION_DENIED; // Denied - not in whitelist
    }
    
    // Default: allow if no whitelist is configured
    return SANDBOX_SUCCESS;
}