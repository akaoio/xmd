/**
 * @file xmd_internal_config_load_file.c
 * @brief Load configuration from file function
 * @author XMD Team
 *
 * Implementation of file-based configuration loading for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/config_internal.h"

/**
 * @brief Load configuration from file
 * @param config Configuration to load into
 * @param file_path Path to configuration file
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_file(xmd_internal_config* config, const char* file_path) {
    if (!config || !file_path) {
        return -1;
    }
    
    FILE* file = fopen(file_path, "r");
    if (!file) {
        return -1;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        
        // Remove trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Find '=' separator
        char* eq = strchr(line, '=');
        if (!eq) {
            continue;
        }
        
        *eq = '\0';
        char* key = line;
        char* value = eq + 1;
        
        // Trim whitespace from key and value
        while (*key == ' ' || *key == '\t') key++;
        while (*value == ' ' || *value == '\t') value++;
        
        // Simple key-value parsing (basic implementation)
        if (strcmp(key, "memory_limit_mb") == 0) {
            config->limits.memory_limit_mb = (size_t)atoi(value);
        } else if (strcmp(key, "cpu_time_limit_ms") == 0) {
            config->limits.cpu_time_limit_ms = (size_t)atoi(value);
        } else if (strcmp(key, "enable_sandbox") == 0) {
            config->security.enable_sandbox = (strcmp(value, "true") == 0);
        }
        // Add more key-value pairs as needed
    }
    
    fclose(file);
    
    // Store the config file path
    free(config->config_file_path);
    config->config_file_path = strdup(file_path);
    
    return 0;
}
