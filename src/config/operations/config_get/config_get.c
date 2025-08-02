/**
 * @file config_get.c
 * @brief Get configuration value by key
 * 
 * This file contains ONLY the config_get function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"
#include <string.h>

/**
 * @brief Get configuration value by key
 * @param config Configuration instance
 * @param key Configuration key
 * @return Configuration value or NULL if not found
 */
const char* config_get(const xmd_internal_config* config, const char* key) {
    XMD_VALIDATE_PTRS(NULL, config, key);
    
    // Handle specific configuration keys
    if (strcmp(key, "config_file_path") == 0) {
        return config->config_file_path;
    }
    
    if (strcmp(key, "number_format") == 0) {
        return config->precision.number_format;
    }
    
    if (strcmp(key, "temp_dir") == 0) {
        return config->paths.temp_dir;
    }
    
    if (strcmp(key, "proc_status_path") == 0) {
        return config->paths.proc_status_path;
    }
    
    if (strcmp(key, "proc_fd_path") == 0) {
        return config->paths.proc_fd_path;
    }
    
    // Key not found
    return NULL;
}