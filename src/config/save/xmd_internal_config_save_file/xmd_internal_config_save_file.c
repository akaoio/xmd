/**
 * @file xmd_internal_config_save_file.c
 * @brief Save configuration to file
 * 
 * This file contains ONLY the xmd_internal_config_save_file function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Save configuration to file
 * @param config Configuration to save
 * @param filename Path to configuration file
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_save_file(const xmd_internal_config* config, const char* filename) {
    XMD_VALIDATE_PTRS(-1, config, filename);
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        return -1;
    }
    
    // Write configuration header
    fprintf(file, "# XMD Configuration File\n");
    fprintf(file, "# Generated automatically\n\n");
    
    // Write resource limits
    fprintf(file, "[Limits]\n");
    fprintf(file, "memory_limit_mb=%zu\n", config->limits.memory_limit_mb);
    fprintf(file, "cpu_time_limit_ms=%zu\n", config->limits.cpu_time_limit_ms);
    fprintf(file, "execution_time_limit_ms=%zu\n", config->limits.execution_time_limit_ms);
    fprintf(file, "max_output_size=%zu\n", config->limits.max_output_size);
    fprintf(file, "max_recursion_depth=%zu\n", config->limits.max_recursion_depth);
    fprintf(file, "max_loop_iterations=%zu\n", config->limits.max_loop_iterations);
    fprintf(file, "\n");
    
    // Write buffer configuration
    fprintf(file, "[Buffers]\n");
    fprintf(file, "line_buffer_size=%zu\n", config->buffers.line_buffer_size);
    fprintf(file, "conversion_buffer_size=%zu\n", config->buffers.conversion_buffer_size);
    fprintf(file, "initial_store_capacity=%zu\n", config->buffers.initial_store_capacity);
    fprintf(file, "store_load_factor=%.2f\n", config->buffers.store_load_factor);
    fprintf(file, "\n");
    
    // Write paths
    fprintf(file, "[Paths]\n");
    if (config->paths.proc_status_path) {
        fprintf(file, "proc_status_path=%s\n", config->paths.proc_status_path);
    }
    if (config->paths.proc_fd_path) {
        fprintf(file, "proc_fd_path=%s\n", config->paths.proc_fd_path);
    }
    if (config->paths.temp_dir) {
        fprintf(file, "temp_dir=%s\n", config->paths.temp_dir);
    }
    fprintf(file, "\n");
    
    // Write security settings
    fprintf(file, "[Security]\n");
    fprintf(file, "enable_sandbox=%s\n", config->security.enable_sandbox ? "true" : "false");
    fprintf(file, "allow_file_access=%s\n", config->security.allow_file_access ? "true" : "false");
    fprintf(file, "allow_network_access=%s\n", config->security.allow_network_access ? "true" : "false");
    
    fclose(file);
    return 0;
}