#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file config_load_file.c
 * @brief Configuration file loading function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

/**
 * @brief Load configuration from file
 * @param config Configuration structure
 * @param file_path Path to configuration file
 * @return 0 on success, -1 on error
 */
int config_load_file(xmd_config* config, const char* file_path) {
    if (!config || !file_path) {
        return -1;
    }
    
    FILE* file = fopen(file_path, "r");
    if (!file) {
        return -1;
    }
    
    // Simple configuration file parsing
    // In a full implementation, this would parse JSON/YAML
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        
        // Look for key=value pairs
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';
            char* key = line;
            char* value_str = equals + 1;
            
            // Remove trailing newline
            char* newline = strchr(value_str, '\n');
            if (newline) {
                *newline = '\0';
            }
            
            // Create value
            config_value* value = malloc(sizeof(config_value));
            if (value) {
                value->type = CONFIG_STRING;
                value->data.string_val = strdup(value_str);
                config_set(config, key, value);
            }
        }
    }
    
    fclose(file);
    
    // Mark configuration as successfully loaded
    // In the current struct design, we don't track load state or file path
    // The configuration values are already set in the struct members above
    
    return 0;
}