/**
 * @file config_set.c
 * @brief Implementation of config_set function
 * 
 * This file contains ONLY the config_set function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_internal.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Set configuration value
 * @param config Configuration to modify
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int config_set(xmd_internal_config* config, const char* key, const char* value) {
    XMD_VALIDATE_PTRS(-1, config, key, value);
    
    // Basic implementation for common configuration keys
    if (strcmp(key, "memory_limit_mb") == 0) {
        long mem_mb = strtol(value, NULL, 10);
        if (mem_mb > 0 && mem_mb <= 16384) { // Reasonable limits: 1MB to 16GB
            config->limits.memory_limit_mb = (size_t)mem_mb;
            return 0;
        }
        return -1;
    }
    
    if (strcmp(key, "execution_time_limit_ms") == 0) {
        long time_ms = strtol(value, NULL, 10);
        if (time_ms > 0 && time_ms <= 3600000) { // Max 1 hour
            config->limits.execution_time_limit_ms = (size_t)time_ms;
            return 0;
        }
        return -1;
    }
    
    if (strcmp(key, "max_recursion_depth") == 0) {
        long depth = strtol(value, NULL, 10);
        if (depth > 0 && depth <= 10000) { // Reasonable recursion limits
            config->limits.max_recursion_depth = (size_t)depth;
            return 0;
        }
        return -1;
    }
    
    if (strcmp(key, "line_buffer_size") == 0) {
        long size = strtol(value, NULL, 10);
        if (size > 0 && size <= 1048576) { // Max 1MB buffer
            config->buffers.line_buffer_size = (size_t)size;
            return 0;
        }
        return -1;
    }
    
    if (strcmp(key, "enable_sandbox") == 0) {
        if (strcmp(value, "true") == 0 || strcmp(value, "1") == 0) {
            config->security.enable_sandbox = true;
            return 0;
        } else if (strcmp(value, "false") == 0 || strcmp(value, "0") == 0) {
            config->security.enable_sandbox = false;
            return 0;
        }
        return -1;
    }
    
    if (strcmp(key, "allow_file_access") == 0) {
        if (strcmp(value, "true") == 0 || strcmp(value, "1") == 0) {
            config->security.allow_file_access = true;
            return 0;
        } else if (strcmp(value, "false") == 0 || strcmp(value, "0") == 0) {
            config->security.allow_file_access = false;
            return 0;
        }
        return -1;
    }
    
    // Unknown configuration key - log warning but don't fail
    fprintf(stderr, "Warning: Unknown configuration key '%s' with value '%s'\n", key, value);
    return 0;
}