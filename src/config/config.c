/**
 * @file config.c
 * @brief Configuration system implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include "../../include/config.h"

// Global configuration instance
static xmd_internal_config* g_config = NULL;

/**
 * @brief Create default resource limits
 */
static xmd_resource_limits create_default_limits(void) {
    xmd_resource_limits limits = {
        .memory_limit_mb = 100,
        .cpu_time_limit_ms = 5000,
        .execution_time_limit_ms = 10000,
        .max_output_size = 1024 * 1024,  // 1MB
        .max_recursion_depth = 100,
        .max_loop_iterations = 10000
    };
    return limits;
}

/**
 * @brief Create default buffer configuration
 */
static xmd_buffer_config create_default_buffers(void) {
    xmd_buffer_config buffers = {
        .line_buffer_size = 256,
        .conversion_buffer_size = 64,
        .initial_store_capacity = 16,
        .store_load_factor = 0.75
    };
    return buffers;
}

/**
 * @brief Create default paths configuration
 */
static xmd_paths_config create_default_paths(void) {
    xmd_paths_config paths = {
        .proc_status_path = strdup("/proc/self/status"),
        .proc_fd_path = strdup("/proc/self/fd"),
        .temp_dir = strdup("/tmp"),
        .module_search_paths = NULL,
        .module_search_path_count = 0
    };
    return paths;
}

/**
 * @brief Create default security configuration
 */
static xmd_security_config create_default_security(void) {
    xmd_security_config security = {
        .exec_whitelist = NULL,
        .exec_whitelist_count = 0,
        .enable_sandbox = true,
        .allow_file_access = true,
        .allow_network_access = false
    };
    
    // Add default whitelist
    security.exec_whitelist = malloc(3 * sizeof(char*));
    if (security.exec_whitelist) {
        security.exec_whitelist[0] = strdup("echo");
        security.exec_whitelist[1] = strdup("date");
        security.exec_whitelist[2] = strdup("cat");
        security.exec_whitelist_count = 3;
    }
    
    return security;
}

/**
 * @brief Create default timing configuration
 */
static xmd_timing_config create_default_timing(void) {
    xmd_timing_config timing = {
        .graceful_shutdown_wait_us = 100000,  // 100ms
        .process_check_interval_us = 10000,   // 10ms
        .cache_ttl_ms = 5 * 60 * 1000        // 5 minutes
    };
    return timing;
}

/**
 * @brief Create default precision configuration
 */
static xmd_precision_config create_default_precision(void) {
    xmd_precision_config precision = {
        .float_epsilon = 1e-10,
        .number_format = "%.6g",
        .int_min_value = -2147483648.0,
        .int_max_value = 2147483647.0
    };
    return precision;
}

/**
 * @brief Create a new configuration with default values
 */
xmd_internal_config* xmd_internal_config_new(void) {
    xmd_internal_config* config = malloc(sizeof(xmd_internal_config));
    if (!config) {
        return NULL;
    }
    
    config->limits = create_default_limits();
    config->buffers = create_default_buffers();
    config->paths = create_default_paths();
    config->security = create_default_security();
    config->timing = create_default_timing();
    config->precision = create_default_precision();
    config->config_file_path = NULL;
    
    return config;
}

/**
 * @brief Free paths configuration
 */
static void free_paths_config(xmd_paths_config* paths) {
    free(paths->proc_status_path);
    free(paths->proc_fd_path);
    free(paths->temp_dir);
    
    for (size_t i = 0; i < paths->module_search_path_count; i++) {
        free(paths->module_search_paths[i]);
    }
    free(paths->module_search_paths);
}

/**
 * @brief Free security configuration
 */
static void free_security_config(xmd_security_config* security) {
    for (size_t i = 0; i < security->exec_whitelist_count; i++) {
        free(security->exec_whitelist[i]);
    }
    free(security->exec_whitelist);
}

/**
 * @brief Free configuration
 */
void xmd_internal_config_free(xmd_internal_config* config) {
    if (!config) {
        return;
    }
    
    free_paths_config(&config->paths);
    free_security_config(&config->security);
    free(config->config_file_path);
    free(config);
}

/**
 * @brief Parse environment variable as size_t
 */
static size_t parse_env_size_t(const char* env_name, size_t default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    char* endptr;
    unsigned long value = strtoul(env_value, &endptr, 10);
    if (*endptr != '\0' || value > SIZE_MAX) {
        return default_value;
    }
    
    return (size_t)value;
}

/**
 * @brief Parse environment variable as double
 */
static double parse_env_double(const char* env_name, double default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    char* endptr;
    double value = strtod(env_value, &endptr);
    if (*endptr != '\0') {
        return default_value;
    }
    
    return value;
}

/**
 * @brief Parse environment variable as boolean
 */
static bool parse_env_bool(const char* env_name, bool default_value) {
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return default_value;
    }
    
    return (strcmp(env_value, "true") == 0 || 
            strcmp(env_value, "1") == 0 ||
            strcmp(env_value, "yes") == 0);
}

/**
 * @brief Load configuration from environment variables
 */
int xmd_internal_config_load_env(xmd_internal_config* config) {
    if (!config) {
        return -1;
    }
    
    // Load resource limits
    config->limits.memory_limit_mb = parse_env_size_t("XMD_MEMORY_LIMIT_MB", config->limits.memory_limit_mb);
    config->limits.cpu_time_limit_ms = parse_env_size_t("XMD_CPU_TIME_LIMIT_MS", config->limits.cpu_time_limit_ms);
    config->limits.execution_time_limit_ms = parse_env_size_t("XMD_EXECUTION_TIME_LIMIT_MS", config->limits.execution_time_limit_ms);
    config->limits.max_output_size = parse_env_size_t("XMD_MAX_OUTPUT_SIZE", config->limits.max_output_size);
    config->limits.max_recursion_depth = parse_env_size_t("XMD_MAX_RECURSION_DEPTH", config->limits.max_recursion_depth);
    config->limits.max_loop_iterations = parse_env_size_t("XMD_MAX_LOOP_ITERATIONS", config->limits.max_loop_iterations);
    
    // Load buffer configuration
    config->buffers.line_buffer_size = parse_env_size_t("XMD_LINE_BUFFER_SIZE", config->buffers.line_buffer_size);
    config->buffers.conversion_buffer_size = parse_env_size_t("XMD_CONVERSION_BUFFER_SIZE", config->buffers.conversion_buffer_size);
    config->buffers.initial_store_capacity = parse_env_size_t("XMD_INITIAL_STORE_CAPACITY", config->buffers.initial_store_capacity);
    config->buffers.store_load_factor = parse_env_double("XMD_STORE_LOAD_FACTOR", config->buffers.store_load_factor);
    
    // Load paths
    const char* proc_status = getenv("XMD_PROC_STATUS_PATH");
    if (proc_status) {
        free(config->paths.proc_status_path);
        config->paths.proc_status_path = strdup(proc_status);
    }
    
    const char* proc_fd = getenv("XMD_PROC_FD_PATH");
    if (proc_fd) {
        free(config->paths.proc_fd_path);
        config->paths.proc_fd_path = strdup(proc_fd);
    }
    
    const char* temp_dir = getenv("XMD_TEMP_DIR");
    if (temp_dir) {
        free(config->paths.temp_dir);
        config->paths.temp_dir = strdup(temp_dir);
    }
    
    // Load security configuration
    config->security.enable_sandbox = parse_env_bool("XMD_ENABLE_SANDBOX", config->security.enable_sandbox);
    config->security.allow_file_access = parse_env_bool("XMD_ALLOW_FILE_ACCESS", config->security.allow_file_access);
    config->security.allow_network_access = parse_env_bool("XMD_ALLOW_NETWORK_ACCESS", config->security.allow_network_access);
    
    // Load timing configuration
    config->timing.graceful_shutdown_wait_us = parse_env_size_t("XMD_GRACEFUL_SHUTDOWN_WAIT_US", config->timing.graceful_shutdown_wait_us);
    config->timing.process_check_interval_us = parse_env_size_t("XMD_PROCESS_CHECK_INTERVAL_US", config->timing.process_check_interval_us);
    config->timing.cache_ttl_ms = parse_env_size_t("XMD_CACHE_TTL_MS", config->timing.cache_ttl_ms);
    
    // Load precision configuration
    config->precision.float_epsilon = parse_env_double("XMD_FLOAT_EPSILON", config->precision.float_epsilon);
    config->precision.int_min_value = parse_env_double("XMD_INT_MIN_VALUE", config->precision.int_min_value);
    config->precision.int_max_value = parse_env_double("XMD_INT_MAX_VALUE", config->precision.int_max_value);
    
    // Load security whitelist
    xmd_internal_config_load_whitelist_env(config, "XMD_EXEC_WHITELIST");
    
    return 0;
}

/**
 * @brief Simple config file parser (key=value format)
 */
int xmd_internal_config_load_file(xmd_internal_config* config, const char* file_path) {
    if (!config || !file_path) {
        return -1;
    }
    
    FILE* file = fopen(file_path, "r");
    if (!file) {
        return -1;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        
        // Remove trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Find '=' separator
        char* eq = strchr(line, '=');
        if (!eq) {
            continue;
        }
        
        *eq = '\0';
        const char* key = line;
        const char* value = eq + 1;
        
        // Parse key-value pairs
        if (strcmp(key, "memory_limit_mb") == 0) {
            config->limits.memory_limit_mb = (size_t)atoll(value);
        } else if (strcmp(key, "cpu_time_limit_ms") == 0) {
            config->limits.cpu_time_limit_ms = (size_t)atoll(value);
        } else if (strcmp(key, "execution_time_limit_ms") == 0) {
            config->limits.execution_time_limit_ms = (size_t)atoll(value);
        } else if (strcmp(key, "max_output_size") == 0) {
            config->limits.max_output_size = (size_t)atoll(value);
        } else if (strcmp(key, "proc_status_path") == 0) {
            free(config->paths.proc_status_path);
            config->paths.proc_status_path = strdup(value);
        } else if (strcmp(key, "proc_fd_path") == 0) {
            free(config->paths.proc_fd_path);
            config->paths.proc_fd_path = strdup(value);
        } else if (strcmp(key, "temp_dir") == 0) {
            free(config->paths.temp_dir);
            config->paths.temp_dir = strdup(value);
        }
        // Add more key parsing as needed
    }
    
    fclose(file);
    
    free(config->config_file_path);
    config->config_file_path = strdup(file_path);
    
    return 0;
}

/**
 * @brief Save configuration to file
 */
int xmd_internal_config_save_file(const xmd_internal_config* config, const char* file_path) {
    if (!config || !file_path) {
        return -1;
    }
    
    FILE* file = fopen(file_path, "w");
    if (!file) {
        return -1;
    }
    
    fprintf(file, "# XMD Configuration File\n");
    fprintf(file, "# Resource Limits\n");
    fprintf(file, "memory_limit_mb=%zu\n", config->limits.memory_limit_mb);
    fprintf(file, "cpu_time_limit_ms=%zu\n", config->limits.cpu_time_limit_ms);
    fprintf(file, "execution_time_limit_ms=%zu\n", config->limits.execution_time_limit_ms);
    fprintf(file, "max_output_size=%zu\n", config->limits.max_output_size);
    fprintf(file, "max_recursion_depth=%zu\n", config->limits.max_recursion_depth);
    fprintf(file, "max_loop_iterations=%zu\n", config->limits.max_loop_iterations);
    
    fprintf(file, "\n# Buffer Configuration\n");
    fprintf(file, "line_buffer_size=%zu\n", config->buffers.line_buffer_size);
    fprintf(file, "conversion_buffer_size=%zu\n", config->buffers.conversion_buffer_size);
    fprintf(file, "initial_store_capacity=%zu\n", config->buffers.initial_store_capacity);
    fprintf(file, "store_load_factor=%.3f\n", config->buffers.store_load_factor);
    
    fprintf(file, "\n# System Paths\n");
    fprintf(file, "proc_status_path=%s\n", config->paths.proc_status_path);
    fprintf(file, "proc_fd_path=%s\n", config->paths.proc_fd_path);
    fprintf(file, "temp_dir=%s\n", config->paths.temp_dir);
    
    fprintf(file, "\n# Security Configuration\n");
    fprintf(file, "enable_sandbox=%s\n", config->security.enable_sandbox ? "true" : "false");
    fprintf(file, "allow_file_access=%s\n", config->security.allow_file_access ? "true" : "false");
    fprintf(file, "allow_network_access=%s\n", config->security.allow_network_access ? "true" : "false");
    
    fclose(file);
    return 0;
}

/**
 * @brief Get global configuration instance
 */
xmd_internal_config* xmd_internal_config_get_global(void) {
    if (!g_config) {
        g_config = xmd_internal_config_new();
        if (g_config) {
            xmd_internal_config_load_env(g_config);
        }
    }
    return g_config;
}

/**
 * @brief Set global configuration instance
 */
void xmd_internal_config_set_global(xmd_internal_config* config) {
    if (g_config && g_config != config) {
        xmd_internal_config_free(g_config);
    }
    g_config = config;
}

/**
 * @brief Add module search path
 */
int xmd_internal_config_add_module_path(xmd_internal_config* config, const char* path) {
    if (!config || !path) {
        return -1;
    }
    
    char** new_paths = realloc(config->paths.module_search_paths,
                              (config->paths.module_search_path_count + 1) * sizeof(char*));
    if (!new_paths) {
        return -1;
    }
    
    config->paths.module_search_paths = new_paths;
    config->paths.module_search_paths[config->paths.module_search_path_count] = strdup(path);
    config->paths.module_search_path_count++;
    
    return 0;
}

/**
 * @brief Add executable to whitelist
 */
int xmd_internal_config_add_exec_whitelist(xmd_internal_config* config, const char* executable) {
    if (!config || !executable) {
        return -1;
    }
    
    char** new_whitelist = realloc(config->security.exec_whitelist,
                                  (config->security.exec_whitelist_count + 1) * sizeof(char*));
    if (!new_whitelist) {
        return -1;
    }
    
    config->security.exec_whitelist = new_whitelist;
    config->security.exec_whitelist[config->security.exec_whitelist_count] = strdup(executable);
    config->security.exec_whitelist_count++;
    
    return 0;
}

/**
 * @brief Set complete executable whitelist (replaces existing)
 */
int xmd_internal_config_set_exec_whitelist(xmd_internal_config* config, const char** executables, size_t count) {
    if (!config) {
        return -1;
    }
    
    // Free existing whitelist
    for (size_t i = 0; i < config->security.exec_whitelist_count; i++) {
        free(config->security.exec_whitelist[i]);
    }
    free(config->security.exec_whitelist);
    
    // Set new whitelist
    if (count == 0 || !executables) {
        config->security.exec_whitelist = NULL;
        config->security.exec_whitelist_count = 0;
        return 0;
    }
    
    config->security.exec_whitelist = malloc(count * sizeof(char*));
    if (!config->security.exec_whitelist) {
        config->security.exec_whitelist_count = 0;
        return -1;
    }
    
    for (size_t i = 0; i < count; i++) {
        config->security.exec_whitelist[i] = strdup(executables[i]);
        if (!config->security.exec_whitelist[i]) {
            // Cleanup on error
            for (size_t j = 0; j < i; j++) {
                free(config->security.exec_whitelist[j]);
            }
            free(config->security.exec_whitelist);
            config->security.exec_whitelist = NULL;
            config->security.exec_whitelist_count = 0;
            return -1;
        }
    }
    
    config->security.exec_whitelist_count = count;
    return 0;
}

/**
 * @brief Load security whitelist from environment variable
 */
int xmd_internal_config_load_whitelist_env(xmd_internal_config* config, const char* env_name) {
    if (!config || !env_name) {
        return -1;
    }
    
    const char* env_value = getenv(env_name);
    if (!env_value) {
        return 0; // No environment variable set, keep current whitelist
    }
    
    // Parse comma-separated list
    char* env_copy = strdup(env_value);
    if (!env_copy) {
        return -1;
    }
    
    // Count entries
    size_t count = 1;
    char* p = env_copy;
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    
    // Allocate array for executable names
    const char** executables = malloc(count * sizeof(char*));
    if (!executables) {
        free(env_copy);
        return -1;
    }
    
    // Parse entries
    size_t i = 0;
    char* token = strtok(env_copy, ",");
    while (token && i < count) {
        // Trim whitespace
        while (*token == ' ' || *token == '\t') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\t')) {
            *end = '\0';
            end--;
        }
        
        executables[i] = token;
        i++;
        token = strtok(NULL, ",");
    }
    
    // Set the whitelist
    int result = xmd_internal_config_set_exec_whitelist(config, executables, i);
    
    free(executables);
    free(env_copy);
    
    return result;
}