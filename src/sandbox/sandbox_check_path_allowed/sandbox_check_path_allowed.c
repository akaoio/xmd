/**
 * @file sandbox_check_path_allowed.c
 * @brief Check if path is allowed
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Check if path is allowed
 * @param ctx Sandbox context
 * @param path Path to check
 * @return SandboxResult indicating allowed/denied
 */
int sandbox_check_path_allowed(SandboxContext* ctx, const char* path) {
    if (!ctx || !ctx->config || !path) return SANDBOX_ERROR;
    
    // Check blocked paths first
    for (size_t i = 0; i < ctx->config->blocked_path_count; i++) {
        if (strstr(path, ctx->config->blocked_paths[i]) != NULL) {
            return SANDBOX_PERMISSION_DENIED; // Denied
        }
    }
    
    // Check allowed paths
    for (size_t i = 0; i < ctx->config->allowed_path_count; i++) {
        if (strstr(path, ctx->config->allowed_paths[i]) != NULL) {
            return SANDBOX_SUCCESS; // Allowed
        }
    }
    
    // If allowed paths are configured but path not found, deny
    if (ctx->config->allowed_path_count > 0) {
        return SANDBOX_PERMISSION_DENIED; // Denied - not in allowed paths
    }
    
    // Default: allow if no path restrictions configured
    return SANDBOX_SUCCESS;
}