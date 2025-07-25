/**
 * @file sandbox.h
 * @brief Security sandbox system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef SANDBOX_H
#define SANDBOX_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sandbox configuration
 */
typedef struct {
    char** command_whitelist;       /**< Allowed commands */
    size_t whitelist_count;         /**< Number of whitelisted commands */
    char** command_blacklist;       /**< Forbidden commands */
    size_t blacklist_count;         /**< Number of blacklisted commands */
    char** allowed_paths;           /**< Allowed file paths */
    size_t allowed_path_count;      /**< Number of allowed paths */
    char** blocked_paths;           /**< Blocked file paths */
    size_t blocked_path_count;      /**< Number of blocked paths */
    long max_memory_mb;             /**< Maximum memory in MB */
    long max_cpu_time_ms;           /**< Maximum CPU time in ms */
    int enable_network;             /**< Whether to allow network access */
} SandboxConfig;

/**
 * @brief Sandbox context
 */
typedef struct sandbox_context SandboxContext;

/**
 * @brief Sandbox result codes
 */
typedef enum {
    SANDBOX_SUCCESS = 0,            /**< Operation successful */
    SANDBOX_ERROR = -1,             /**< General error */
    SANDBOX_PERMISSION_DENIED = -2, /**< Permission denied */
    SANDBOX_RESOURCE_LIMIT = -3     /**< Resource limit exceeded */
} SandboxResult;

/**
 * @brief Create a new sandbox configuration
 * @return New sandbox configuration or NULL on error
 */
SandboxConfig* sandbox_config_new(void);

/**
 * @brief Free a sandbox configuration
 * @param config Configuration to free
 */
void sandbox_config_free(SandboxConfig* config);

/**
 * @brief Add command to whitelist
 * @param config Sandbox configuration
 * @param command Command to whitelist
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_whitelist(SandboxConfig* config, const char* command);

/**
 * @brief Add path to allowed paths
 * @param config Sandbox configuration
 * @param path Path to allow
 * @return SandboxResult indicating success/failure
 */
int sandbox_config_add_allowed_path(SandboxConfig* config, const char* path);

/**
 * @brief Create a new sandbox context
 * @param config Sandbox configuration
 * @return New sandbox context or NULL on error
 */
SandboxContext* sandbox_context_new(SandboxConfig* config);

/**
 * @brief Free a sandbox context
 * @param ctx Sandbox context to free
 */
void sandbox_context_free(SandboxContext* ctx);

/**
 * @brief Check if command is allowed
 * @param ctx Sandbox context
 * @param command Command to check
 * @return SandboxResult indicating allowed/denied
 */
int sandbox_check_command_allowed(SandboxContext* ctx, const char* command);

/**
 * @brief Check if path is allowed
 * @param ctx Sandbox context
 * @param path Path to check
 * @return SandboxResult indicating allowed/denied
 */
int sandbox_check_path_allowed(SandboxContext* ctx, const char* path);

/**
 * @brief Apply resource limits
 * @param ctx Sandbox context
 * @return SandboxResult indicating success/failure
 */
int sandbox_apply_limits(SandboxContext* ctx);

#ifdef __cplusplus
}
#endif

#endif /* SANDBOX_H */