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
 * @brief Extract command name from full command string
 * @param command Full command string
 * @param cmd_name Buffer to store command name
 * @param cmd_name_size Size of command name buffer
 * @return 0 on success, -1 on error
 */
static int extract_command_name(const char* command, char* cmd_name, size_t cmd_name_size) {
    if (!command || !cmd_name || cmd_name_size == 0) return -1;
    
    // Skip leading whitespace
    while (*command && (*command == ' ' || *command == '\t')) {
        command++;
    }
    
    // Copy command name until first space or end of string
    size_t i = 0;
    while (*command && *command != ' ' && *command != '\t' && i < cmd_name_size - 1) {
        cmd_name[i++] = *command++;
    }
    cmd_name[i] = '\0';
    
    return i > 0 ? 0 : -1;
}

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

/**
 * @brief Apply resource limits
 * @param ctx Sandbox context
 * @return SandboxResult indicating success/failure
 */
int sandbox_apply_limits(SandboxContext* ctx) {
    if (!ctx || !ctx->config) return SANDBOX_ERROR;
    
    // This is a stub implementation - resource limits would be applied here
    // In a real implementation, this would set up memory limits, CPU time limits, etc.
    return SANDBOX_SUCCESS;
}