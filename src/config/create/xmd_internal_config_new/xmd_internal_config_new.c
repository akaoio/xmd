/**
 * @file xmd_internal_config_new.c
 * @brief Create new internal configuration with defaults
 * 
 * This file contains ONLY the xmd_internal_config_new function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Create new internal configuration with default values
 * @return New configuration or NULL on error
 */
xmd_internal_config* xmd_internal_config_new(void) {
    xmd_internal_config* config;
    XMD_MALLOC_DYNAMIC(config, sizeof(xmd_internal_config), NULL);
    
    // Initialize with default values
    memset(config, 0, sizeof(xmd_internal_config));
    
    // Set default resource limits
    config->limits.memory_limit_mb = 128;
    config->limits.cpu_time_limit_ms = 5000;
    config->limits.execution_time_limit_ms = 10000;
    config->limits.max_output_size = 1024 * 1024; // 1MB
    config->limits.max_recursion_depth = 100;
    config->limits.max_loop_iterations = 10000;
    
    // Set default buffer configuration
    config->buffers.line_buffer_size = 4096;
    config->buffers.conversion_buffer_size = 1024;
    config->buffers.initial_store_capacity = 32;
    config->buffers.store_load_factor = 0.75;
    
    // Set default timing configuration
    config->timing.graceful_shutdown_wait_us = 1000000; // 1 second
    config->timing.process_check_interval_us = 100000;  // 100ms
    config->timing.cache_ttl_ms = 300000; // 5 minutes
    
    // Set default precision configuration
    config->precision.float_epsilon = 1e-9;
    config->precision.number_format = strdup("%.6g");
    config->precision.int_min_value = -2147483648.0;
    config->precision.int_max_value = 2147483647.0;
    
    // Initialize paths
    config->paths.proc_status_path = strdup("/proc/self/status");
    config->paths.proc_fd_path = strdup("/proc/self/fd");
    config->paths.temp_dir = strdup("/tmp");
    config->paths.module_search_paths = NULL;
    config->paths.module_search_path_count = 0;
    
    // Initialize security defaults
    config->security.exec_whitelist = NULL;
    config->security.exec_whitelist_count = 0;
    config->security.enable_sandbox = true;
    config->security.allow_file_access = true;
    config->security.allow_network_access = false;
    
    // Initialize config file path
    config->config_file_path = NULL;
    
    return config;
}