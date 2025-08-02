/**
 * @file config_consolidated.c
 * @brief Consolidated configuration system for XMD
 * @author XMD Development Team
 *
 * All configuration functionality consolidated from config/ directory.
 * Includes global configuration variables, default creation, and management.
 * Moved to src level to eliminate config/ directory for 95% milestone.
 */

#include "../include/config_internal.h"
#include "../include/xmd.h"
#include "../include/memory.h"
#include "../include/utils.h"

// ============================================================================
// GLOBAL CONFIGURATION VARIABLES (FROM config_globals DIRECTORY)
// ============================================================================

// Global configuration instance definition
xmd_internal_config* g_config = NULL;

// Configuration value types
typedef enum {
    CONFIG_STRING,
    CONFIG_INT,
    CONFIG_BOOL,
    CONFIG_DOUBLE
} config_value_type;

// Configuration value structure
typedef struct config_value {
    config_value_type type;
    union {
        char* string_val;
        int int_val;
        bool bool_val;
        double double_val;
    } data;
} config_value;

// ============================================================================
// DEFAULT CONFIGURATION CREATION
// ============================================================================

/**
 * @brief Create default resource limits
 * @return Default resource limits configuration
 */
xmd_resource_limits create_default_limits(void) {
    xmd_resource_limits limits;
    
    // Memory limits
    limits.memory_limit_mb = 64; // 64MB default
    limits.cpu_time_limit_ms = 30000; // 30 seconds CPU time
    limits.execution_time_limit_ms = 30000; // 30 seconds wall time
    limits.max_output_size = 10 * 1024 * 1024; // 10MB output
    limits.max_recursion_depth = 1000; // Stack depth limit
    limits.max_loop_iterations = 100000; // Loop iteration limit
    
    return limits;
}

/**
 * @brief Create default buffer sizes
 * @return Default buffer configuration
 */
xmd_buffer_config create_default_buffers(void) {
    xmd_buffer_config buffers;
    
    buffers.line_buffer_size = 1024;         // 1KB line buffer
    buffers.conversion_buffer_size = 4096;   // 4KB conversion buffer 
    buffers.initial_store_capacity = 64;     // Initial store capacity
    buffers.store_load_factor = 0.75;        // Load factor threshold
    
    return buffers;
}

/**
 * @brief Create default file paths
 * @return Default paths configuration
 */
xmd_paths_config create_default_paths(void) {
    xmd_paths_config paths;
    
    // Initialize paths according to actual struct definition
    paths.proc_status_path = xmd_strdup("/proc/self/status");
    paths.proc_fd_path = xmd_strdup("/proc/self/fd"); 
    paths.temp_dir = xmd_strdup("/tmp");
    paths.module_search_paths = NULL;
    paths.module_search_path_count = 0;
    
    return paths;
}

/**
 * @brief Create default precision settings
 * @return Default precision configuration
 */
xmd_precision_config create_default_precision(void) {
    xmd_precision_config precision;
    
    precision.float_epsilon = 1e-10;   // Floating point comparison epsilon
    precision.number_format = "%.6g";  // Number format string
    precision.int_min_value = -2147483648.0; // Minimum integer value
    precision.int_max_value = 2147483647.0;  // Maximum integer value
    
    return precision;
}

/**
 * @brief Create default security settings
 * @return Default security configuration
 */
xmd_security_config create_default_security(void) {
    xmd_security_config security;
    
    security.exec_whitelist = NULL;
    security.exec_whitelist_count = 0;
    security.enable_sandbox = false;
    security.allow_file_access = true;
    security.allow_network_access = false;
    
    return security;
}

/**
 * @brief Create default timing settings
 * @return Default timing configuration
 */
xmd_timing_config create_default_timing(void) {
    xmd_timing_config timing;
    
    timing.graceful_shutdown_wait_us = 100000; // 100ms graceful shutdown wait
    timing.process_check_interval_us = 1000;   // 1ms process check interval
    timing.cache_ttl_ms = 3600000;             // 1 hour cache TTL
    
    return timing;
}

// ============================================================================
// CONFIGURATION MANAGEMENT
// ============================================================================

/**
 * @brief Create new configuration with defaults
 * @return New configuration instance or NULL on failure
 */
xmd_config* config_create(void) {
    xmd_internal_config* config = xmd_calloc(1, sizeof(xmd_internal_config));
    if (!config) return NULL;
    
    // Set up default values
    config->limits = create_default_limits();
    config->buffers = create_default_buffers();
    config->paths = create_default_paths();
    config->precision = create_default_precision();
    config->security = create_default_security();
    config->timing = create_default_timing();
    
    // Configuration created successfully
    
    return (xmd_config*)config;
}

/**
 * @brief Free configuration and all associated resources
 * @param config Configuration to free
 */
void config_destroy(xmd_config* config) {
    if (!config) return;
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    // Free path strings (only the ones that exist in the struct)
    free(internal->paths.proc_status_path);
    free(internal->paths.proc_fd_path);
    free(internal->paths.temp_dir);
    
    // Free module search paths if they exist
    if (internal->paths.module_search_paths) {
        for (size_t i = 0; i < internal->paths.module_search_path_count; i++) {
            free(internal->paths.module_search_paths[i]);
        }
        free(internal->paths.module_search_paths);
    }
    
    // Free security exec whitelist
    if (internal->security.exec_whitelist) {
        for (size_t i = 0; i < internal->security.exec_whitelist_count; i++) {
            free(internal->security.exec_whitelist[i]);
        }
        free(internal->security.exec_whitelist);
    }
    
    free(config);
}

/**
 * @brief Load configuration from environment variables
 * @param config Configuration to update
 * @return 0 on success, -1 on error
 */
int config_load_env(xmd_config* config) {
    if (!config) return -1;
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    // Load memory limits from environment
    const char* max_memory = getenv("XMD_MAX_MEMORY");
    if (max_memory) {
        internal->limits.memory_limit_mb = (size_t)strtoul(max_memory, NULL, 10);
    }
    
    const char* max_time = getenv("XMD_MAX_TIME");
    if (max_time) {
        internal->limits.execution_time_limit_ms = (size_t)strtoul(max_time, NULL, 10);
    }
    
    // Load security settings
    const char* sandbox = getenv("XMD_SANDBOX");
    if (sandbox) {
        internal->security.enable_sandbox = (strcmp(sandbox, "1") == 0 || 
                                           strcmp(sandbox, "true") == 0);
    }
    
    const char* allow_files = getenv("XMD_ALLOW_FILES");
    if (allow_files) {
        internal->security.allow_file_access = (strcmp(allow_files, "1") == 0 || 
                                              strcmp(allow_files, "true") == 0);
    }
    
    return 0;
}

/**
 * @brief Load configuration from file
 * @param config Configuration to update
 * @param filename Configuration file path
 * @return 0 on success, -1 on error
 */
int config_load_file(xmd_config* config, const char* filename) {
    if (!config || !filename) return -1;
    
    FILE* file = fopen(filename, "r");
    if (!file) return -1;
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';
        
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') continue;
        
        // Parse key=value pairs
        char* equals = strchr(line, '=');
        if (!equals) continue;
        
        *equals = '\0';
        const char* key = line;
        const char* value = equals + 1;
        
        // Process configuration values
        // (Implementation would handle specific config keys)
        (void)key; (void)value; // Suppress unused warnings for now
    }
    
    fclose(file);
    return 0;
}

/**
 * @brief Get global configuration instance
 * @return Global configuration or NULL if not initialized
 */
xmd_config* config_get_global(void) {
    return (xmd_config*)g_config;
}

/**
 * @brief Set global configuration instance
 * @param config Configuration to set as global
 */
void config_set_global(xmd_config* config) {
    g_config = (xmd_internal_config*)config;
}