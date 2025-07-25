/**
 * @file sandbox.c
 * @brief Basic stub implementation of sandbox functionality
 * @author XMD Implementation Team
 * @date 2025-07-25
 * 
 * This is a minimal stub implementation to allow building and testing.
 * The sandbox functionality is not fully implemented yet.
 */

#include "../../include/sandbox.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Create a new sandbox configuration
 * @return New sandbox configuration or NULL on error
 */
SandboxConfig* sandbox_config_new(void) {
    SandboxConfig* config = malloc(sizeof(SandboxConfig));
    if (!config) return NULL;
    
    memset(config, 0, sizeof(SandboxConfig));
    return config;
}

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

/**
 * @brief Add command to whitelist
 * @param config Sandbox configuration
 * @param command Command to whitelist
 * @return 0 on success, -1 on error
 */
int sandbox_config_add_whitelist(SandboxConfig* config, const char* command) {
    if (!config || !command) return -1;
    
    // Reallocate whitelist array
    char** new_whitelist = realloc(config->command_whitelist, 
                                   (config->whitelist_count + 1) * sizeof(char*));
    if (!new_whitelist) return -1;
    
    config->command_whitelist = new_whitelist;
    config->command_whitelist[config->whitelist_count] = strdup(command);
    if (!config->command_whitelist[config->whitelist_count]) return -1;
    
    config->whitelist_count++;
    return 0;
}

/**
 * @brief Add path to allowed paths
 * @param config Sandbox configuration
 * @param path Path to allow
 * @return 0 on success, -1 on error
 */
int sandbox_config_add_allowed_path(SandboxConfig* config, const char* path) {
    if (!config || !path) return -1;
    
    // Reallocate allowed paths array
    char** new_paths = realloc(config->allowed_paths, 
                               (config->allowed_path_count + 1) * sizeof(char*));
    if (!new_paths) return -1;
    
    config->allowed_paths = new_paths;
    config->allowed_paths[config->allowed_path_count] = strdup(path);
    if (!config->allowed_paths[config->allowed_path_count]) return -1;
    
    config->allowed_path_count++;
    return 0;
}

/**
 * @brief Create a new sandbox context
 * @param config Sandbox configuration
 * @return New sandbox context or NULL on error
 */
SandboxContext* sandbox_context_new(SandboxConfig* config) {
    if (!config) return NULL;
    
    SandboxContext* ctx = malloc(sizeof(SandboxContext));
    if (!ctx) return NULL;
    
    ctx->config = config;
    return ctx;
}

/**
 * @brief Free a sandbox context
 * @param ctx Sandbox context to free
 */
void sandbox_context_free(SandboxContext* ctx) {
    if (ctx) {
        free(ctx);
    }
}

/**
 * @brief Check if command is allowed
 * @param ctx Sandbox context
 * @param command Command to check
 * @return 0 if allowed, -1 if denied or error
 */
int sandbox_check_command_allowed(SandboxContext* ctx, const char* command) {
    if (!ctx || !ctx->config || !command) return -1;
    
    // Check whitelist first
    for (size_t i = 0; i < ctx->config->whitelist_count; i++) {
        if (strcmp(ctx->config->command_whitelist[i], command) == 0) {
            return 0; // Allowed
        }
    }
    
    // Check blacklist
    for (size_t i = 0; i < ctx->config->blacklist_count; i++) {
        if (strcmp(ctx->config->command_blacklist[i], command) == 0) {
            return -1; // Denied
        }
    }
    
    // If not in whitelist and whitelist exists, deny
    if (ctx->config->whitelist_count > 0) {
        return -1; // Denied - not in whitelist
    }
    
    // Default: allow if no whitelist is configured
    return 0;
}

/**
 * @brief Check if path is allowed
 * @param ctx Sandbox context
 * @param path Path to check
 * @return 0 if allowed, -1 if denied or error
 */
int sandbox_check_path_allowed(SandboxContext* ctx, const char* path) {
    if (!ctx || !ctx->config || !path) return -1;
    
    // Check blocked paths first
    for (size_t i = 0; i < ctx->config->blocked_path_count; i++) {
        if (strstr(path, ctx->config->blocked_paths[i]) != NULL) {
            return -1; // Denied
        }
    }
    
    // Check allowed paths
    for (size_t i = 0; i < ctx->config->allowed_path_count; i++) {
        if (strstr(path, ctx->config->allowed_paths[i]) != NULL) {
            return 0; // Allowed
        }
    }
    
    // If allowed paths are configured but path not found, deny
    if (ctx->config->allowed_path_count > 0) {
        return -1; // Denied - not in allowed paths
    }
    
    // Default: allow if no path restrictions configured
    return 0;
}