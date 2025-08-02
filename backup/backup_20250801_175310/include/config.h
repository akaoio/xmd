/**
 * @file config.h
 * @brief Configuration system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef XMD_CONFIG_H
#define XMD_CONFIG_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Resource limits configuration
 */
typedef struct xmd_resource_limits {
    size_t memory_limit_mb;          /**< Memory limit in MB */
    size_t cpu_time_limit_ms;        /**< CPU time limit in milliseconds */
    size_t execution_time_limit_ms;  /**< Wall time limit in milliseconds */
    size_t max_output_size;          /**< Maximum output size in bytes */
    size_t max_recursion_depth;      /**< Maximum recursion depth */
    size_t max_loop_iterations;      /**< Maximum loop iterations */
} xmd_resource_limits;

/**
 * @brief Buffer size configuration
 */
typedef struct xmd_buffer_config {
    size_t line_buffer_size;         /**< Line buffer size for file operations */
    size_t conversion_buffer_size;   /**< Buffer size for type conversions */
    size_t initial_store_capacity;   /**< Initial capacity for stores */
    double store_load_factor;        /**< Load factor threshold for stores */
} xmd_buffer_config;

/**
 * @brief System paths configuration
 */
typedef struct xmd_paths_config {
    char* proc_status_path;          /**< Path to process status (default: /proc/self/status) */
    char* proc_fd_path;              /**< Path to process file descriptors (default: /proc/self/fd) */
    char* temp_dir;                  /**< Temporary directory path */
    char** module_search_paths;      /**< Module search paths */
    size_t module_search_path_count; /**< Number of module search paths */
} xmd_paths_config;

/**
 * @brief Security configuration
 */
typedef struct xmd_security_config {
    char** exec_whitelist;           /**< List of allowed executables */
    size_t exec_whitelist_count;     /**< Number of allowed executables */
    bool enable_sandbox;             /**< Enable sandboxing */
    bool allow_file_access;          /**< Allow file system access */
    bool allow_network_access;       /**< Allow network access */
} xmd_security_config;

/**
 * @brief Timing configuration
 */
typedef struct xmd_timing_config {
    size_t graceful_shutdown_wait_us; /**< Graceful shutdown wait in microseconds */
    size_t process_check_interval_us; /**< Process check interval in microseconds */
    size_t cache_ttl_ms;             /**< Cache TTL in milliseconds */
} xmd_timing_config;

/**
 * @brief Numerical precision configuration
 */
typedef struct xmd_precision_config {
    double float_epsilon;            /**< Epsilon for floating point comparisons */
    const char* number_format;       /**< Format string for number display */
    double int_min_value;            /**< Minimum integer value */
    double int_max_value;            /**< Maximum integer value */
} xmd_precision_config;

/**
 * @brief Complete XMD internal configuration
 */
typedef struct xmd_internal_config {
    xmd_resource_limits limits;      /**< Resource limits */
    xmd_buffer_config buffers;       /**< Buffer configuration */
    xmd_paths_config paths;          /**< System paths */
    xmd_security_config security;    /**< Security settings */
    xmd_timing_config timing;        /**< Timing configuration */
    xmd_precision_config precision;  /**< Numerical precision */
    char* config_file_path;          /**< Path to configuration file */
} xmd_internal_config;

/**
 * @brief Create a new configuration with default values
 * @return New configuration or NULL on error
 */
xmd_internal_config* xmd_internal_config_new(void);

/**
 * @brief Free configuration
 * @param config Configuration to free
 */
void xmd_internal_config_free(xmd_internal_config* config);

/**
 * @brief Load configuration from file
 * @param config Configuration to populate
 * @param file_path Path to configuration file
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_file(xmd_internal_config* config, const char* file_path);

/**
 * @brief Save configuration to file
 * @param config Configuration to save
 * @param file_path Path to configuration file
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_save_file(const xmd_internal_config* config, const char* file_path);

/**
 * @brief Load configuration from environment variables
 * @param config Configuration to populate
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_env(xmd_internal_config* config);

/**
 * @brief Get global configuration instance
 * @return Global configuration instance
 */
xmd_internal_config* xmd_internal_config_get_global(void);

/**
 * @brief Set global configuration instance
 * @param config Configuration to set as global
 */
void xmd_internal_config_set_global(xmd_internal_config* config);

/**
 * @brief Add module search path
 * @param config Configuration
 * @param path Path to add
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_add_module_path(xmd_internal_config* config, const char* path);

/**
 * @brief Add executable to whitelist
 * @param config Configuration
 * @param executable Executable name to add
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_add_exec_whitelist(xmd_internal_config* config, const char* executable);

/**
 * @brief Set complete executable whitelist (replaces existing)
 * @param config Configuration
 * @param executables Array of executable names
 * @param count Number of executables
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_set_exec_whitelist(xmd_internal_config* config, const char** executables, size_t count);

/**
 * @brief Load security whitelist from environment variable
 * @param config Configuration
 * @param env_name Environment variable name (e.g., "XMD_EXEC_WHITELIST")
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_whitelist_env(xmd_internal_config* config, const char* env_name);

#endif /* XMD_CONFIG_H */
