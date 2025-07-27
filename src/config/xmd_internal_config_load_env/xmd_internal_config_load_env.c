/**
 * @file xmd_internal_config_load_env.c
 * @brief Load configuration from environment variables
 * @author XMD Team
 *
 * Implementation of environment variable configuration loading for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/config_internal.h"

/**
 * @brief Load configuration from environment variables
 * @param config Configuration to load into
 * @return 0 on success, -1 on error
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
    
    return 0;
}
