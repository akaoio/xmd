/**
 * @file xmd_internal_config_save_file.c
 * @brief Save configuration to file function
 * @author XMD Team
 *
 * Implementation of file-based configuration saving for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Save configuration to file
 * @param config Configuration to save
 * @param file_path Path to save configuration file
 * @return 0 on success, -1 on error
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
    
    fprintf(file, "\n# Security Configuration\n");
    fprintf(file, "enable_sandbox=%s\n", config->security.enable_sandbox ? "true" : "false");
    fprintf(file, "allow_file_access=%s\n", config->security.allow_file_access ? "true" : "false");
    fprintf(file, "allow_network_access=%s\n", config->security.allow_network_access ? "true" : "false");
    
    fprintf(file, "\n# Timing Configuration\n");
    fprintf(file, "graceful_shutdown_wait_us=%zu\n", config->timing.graceful_shutdown_wait_us);
    fprintf(file, "process_check_interval_us=%zu\n", config->timing.process_check_interval_us);
    fprintf(file, "cache_ttl_ms=%zu\n", config->timing.cache_ttl_ms);
    
    fprintf(file, "\n# Precision Configuration\n");
    fprintf(file, "float_epsilon=%.9f\n", config->precision.float_epsilon);
    fprintf(file, "int_min_value=%.0f\n", config->precision.int_min_value);
    fprintf(file, "int_max_value=%.0f\n", config->precision.int_max_value);
    
    fclose(file);
    return 0;
}