/**
 * @file xmd_stubs.c
 * @brief Stub implementations for XMD API functions
 * @author XMD Team
 * 
 * Temporary stub implementations to allow compilation while Phase 1 is in development.
 * These will be replaced with actual implementations in later phases.
 */

#include "../include/xmd.h"
#include "../include/config.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get version information
 * @return Version string
 */
const char* xmd_get_version(void) {
    return XMD_VERSION_STRING;
}

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Human-readable error message
 */
const char* xmd_error_string(xmd_error_code error_code) {
    switch (error_code) {
        case XMD_SUCCESS: return "Success";
        case XMD_ERROR_PARSE: return "Parse error";
        case XMD_ERROR_SYNTAX: return "Syntax error";
        case XMD_ERROR_PERMISSION: return "Permission denied";
        case XMD_ERROR_MODULE_NOT_FOUND: return "Module not found";
        case XMD_ERROR_CIRCULAR_DEPENDENCY: return "Circular dependency";
        case XMD_ERROR_COMMAND_FAILED: return "Command failed";
        case XMD_ERROR_OUT_OF_MEMORY: return "Out of memory";
        case XMD_ERROR_TIMEOUT: return "Operation timed out";
        case XMD_ERROR_INVALID_ARGUMENT: return "Invalid argument";
        case XMD_ERROR_FILE_NOT_FOUND: return "File not found";
        default: return "Unknown error";
    }
}

/**
 * @brief Create default XMD configuration
 * @return Default configuration structure
 */
xmd_config* xmd_config_create_default(void) {
    xmd_config* config = malloc(sizeof(xmd_config));
    if (config == NULL) {
        return NULL;
    }
    
    // Initialize with defaults
    config->sandbox = malloc(sizeof(xmd_sandbox_config));
    if (config->sandbox == NULL) {
        free(config);
        return NULL;
    }
    
    // Get settings from internal configuration system
    xmd_internal_config* internal_config = xmd_internal_config_get_global();
    
    // Copy exec whitelist from internal config
    if (internal_config->security.exec_whitelist_count > 0) {
        config->sandbox->exec_whitelist = malloc(sizeof(char*) * (internal_config->security.exec_whitelist_count + 1));
        for (size_t i = 0; i < internal_config->security.exec_whitelist_count; i++) {
            config->sandbox->exec_whitelist[i] = strdup(internal_config->security.exec_whitelist[i]);
        }
        config->sandbox->exec_whitelist[internal_config->security.exec_whitelist_count] = NULL;
    } else {
        config->sandbox->exec_whitelist = NULL;
    }
    
    config->sandbox->exec_blacklist = NULL;
    config->sandbox->allowed_paths = NULL;
    config->sandbox->blocked_paths = NULL;
    config->sandbox->allowed_networks = NULL;
    config->sandbox->max_memory_mb = (uint32_t)internal_config->limits.memory_limit_mb;
    config->sandbox->max_cpu_time_ms = (uint32_t)internal_config->limits.cpu_time_limit_ms;
    config->sandbox->max_wall_time_ms = (uint32_t)internal_config->limits.execution_time_limit_ms;
    config->sandbox->allow_network = internal_config->security.allow_network_access;
    config->sandbox->allow_filesystem_write = internal_config->security.allow_file_access;
    
    // Other settings from internal config
    config->max_recursion_depth = (uint32_t)internal_config->limits.max_recursion_depth;
    config->max_loop_iterations = (uint32_t)internal_config->limits.max_loop_iterations;
    config->cache_max_memory = internal_config->timing.cache_ttl_ms; // Use cache TTL for max memory temporarily
    config->cache_default_ttl_ms = (uint32_t)internal_config->timing.cache_ttl_ms;
    config->module_search_paths = NULL;
    config->search_path_count = 0;
    config->preserve_comments = true;
    config->pretty_print = false;
    config->output_format = strdup("markdown");
    config->debug_mode = false;
    config->trace_execution = false;
    config->log_level = strdup("info");
    
    return config;
}

/**
 * @brief Free XMD configuration
 * @param config Configuration to free
 */
void xmd_config_free(xmd_config* config) {
    if (config == NULL) {
        return;
    }
    
    if (config->sandbox) {
        if (config->sandbox->exec_whitelist) {
            for (char** ptr = config->sandbox->exec_whitelist; *ptr; ptr++) {
                free(*ptr);
            }
            free(config->sandbox->exec_whitelist);
        }
        free(config->sandbox);
    }
    
    free(config->output_format);
    free(config->log_level);
    free(config);
}

/**
 * @brief Create a new XMD configuration with default values
 * @return New configuration or NULL on error
 */
xmd_config* xmd_config_new(void) {
    return xmd_config_create_default();
}

/**
 * @brief Create XMD processor (stub)
 * @param config Configuration
 * @return NULL (not implemented)
 */
xmd_processor* xmd_processor_create(const xmd_config* config) {
    (void)config; // Suppress unused parameter warning
    return NULL; // Not implemented in Phase 1
}

/**
 * @brief Free XMD processor (stub)
 * @param processor Processor to free
 */
void xmd_processor_free(xmd_processor* processor) {
    (void)processor; // Suppress unused parameter warning
    // Not implemented in Phase 1
}

// xmd_process_string, xmd_process_file, and xmd_result_free are now implemented in c_api.c

/**
 * @brief Validate syntax (stub)
 * @param input Input markdown
 * @param input_length Input length
 * @return XMD_SUCCESS (stub)
 */
xmd_error_code xmd_validate_syntax(const char* input, size_t input_length) {
    (void)input;
    (void)input_length;
    return XMD_SUCCESS; // Stub implementation
}

/**
 * @brief Set variable (stub)
 * @param processor Processor instance
 * @param key Variable name
 * @param value Variable value
 * @return XMD_SUCCESS (stub)
 */
xmd_error_code xmd_set_variable(xmd_processor* processor, const char* key, const char* value) {
    (void)processor;
    (void)key;
    (void)value;
    return XMD_SUCCESS; // Stub implementation
}

/**
 * @brief Get variable (stub)
 * @param processor Processor instance
 * @param key Variable name
 * @return NULL (stub)
 */
char* xmd_get_variable(xmd_processor* processor, const char* key) {
    (void)processor;
    (void)key;
    return NULL; // Stub implementation
}

// xmd_init and xmd_cleanup are now implemented in c_api.c