/**
 * @file xmd_internal_config_load_file.c
 * @brief Load configuration from file
 * 
 * This file contains ONLY the xmd_internal_config_load_file function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../utils/common/common_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Load configuration from file
 * @param config Configuration to load into
 * @param filename Path to configuration file
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_file(xmd_internal_config* config, const char* filename) {
    XMD_VALIDATE_PTRS(-1, config, filename);
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    
    char line[256];
    char key[128];
    char value[128];
    
    // Simple key=value parser
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }
        
        // Parse key=value format
        char* equals = strchr(line, '=');
        if (!equals) {
            continue;
        }
        
        *equals = '\0';
        strncpy(key, line, sizeof(key) - 1);
        key[sizeof(key) - 1] = '\0';
        
        strncpy(value, equals + 1, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
        
        // Remove trailing newline
        char* newline = strchr(value, '\n');
        if (newline) {
            *newline = '\0';
        }
        
        // Set configuration value
        config_set(config, key, value);
    }
    
    fclose(file);
    
    // Store the config file path
    XMD_FREE_SAFE(config->config_file_path);
    config->config_file_path = strdup(filename);
    
    return 0;
}