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
    if (!ctx || !ctx->config || !path) return 0; // Error treated as denied (false)
    
    // Check blocked paths first
    if (ctx->config->blocked_paths != NULL) {
        for (size_t i = 0; i < ctx->config->blocked_path_count; i++) {
            if (ctx->config->blocked_paths[i] != NULL &&
                strlen(ctx->config->blocked_paths[i]) > 0 &&
                strstr(path, ctx->config->blocked_paths[i]) != NULL) {
                return 0; // Denied (false)
            }
        }
    }
    
    // Check allowed paths
    if (ctx->config->allowed_paths != NULL) {
        for (size_t i = 0; i < ctx->config->allowed_path_count; i++) {
            if (ctx->config->allowed_paths[i] != NULL &&
                strlen(ctx->config->allowed_paths[i]) > 0 &&
                strstr(path, ctx->config->allowed_paths[i]) != NULL) {
                return 1; // Allowed (true)
            }
        }
    }
    
    // If allowed paths are configured but path not found, deny
    if (ctx->config->allowed_path_count > 0) {
        return 0; // Denied - not in allowed paths (false)
    }
    
    // Default: allow if no path restrictions configured
    return 1; // Allowed (true)
}