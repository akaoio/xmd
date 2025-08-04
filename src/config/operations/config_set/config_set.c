/**
 * @file config_set.c
 * @brief Set configuration value by key
 * 
 * This file contains ONLY the config_set function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../../utils/common/common_macros.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Set configuration value by key
 * @param config Configuration instance
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int config_set(xmd_internal_config* config, const char* key, const char* value) {
    XMD_VALIDATE_PTRS(-1, config, key, value);
    
    // Handle specific configuration keys
    if (strcmp(key, "config_file_path") == 0) {
        XMD_FREE_SAFE(config->config_file_path);
        config->config_file_path = strdup(value);
        return config->config_file_path ? 0 : -1;
    }
    
    if (strcmp(key, "temp_dir") == 0) {
        XMD_FREE_SAFE(config->paths.temp_dir);
        config->paths.temp_dir = strdup(value);
        return config->paths.temp_dir ? 0 : -1;
    }
    
    if (strcmp(key, "proc_status_path") == 0) {
        XMD_FREE_SAFE(config->paths.proc_status_path);
        config->paths.proc_status_path = strdup(value);
        return config->paths.proc_status_path ? 0 : -1;
    }
    
    if (strcmp(key, "proc_fd_path") == 0) {
        XMD_FREE_SAFE(config->paths.proc_fd_path);
        config->paths.proc_fd_path = strdup(value);
        return config->paths.proc_fd_path ? 0 : -1;
    }
    
    // Key not found or read-only
    return -1;
}