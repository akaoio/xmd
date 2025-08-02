/**
 * @file config_load_file.c
 * @brief Implementation of config_load_file function
 * 
 * This file contains ONLY the config_load_file function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * @brief Load configuration from file
 * @param config Configuration to update
 * @param filename File to load from
 * @return 0 on success, -1 on error
  * /
 */
int config_load_file(xmd_config* config, const char* filename) {
    if (!config || !filename) return -1;
    
    FILE* file = fopen(filename, "r");
    if (!file) return -1;
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';
        
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') continue;
        
        // Parse key=value pairs
        char* equals = strchr(line, '=');
        if (!equals) continue;
        *equals = '\0';
        
        char* key = line;
        char* value = equals + 1;
        
        // Basic config loading (can be expanded)
        xmd_internal_config* internal = (xmd_internal_config*)config;
        if (strcmp(key, "memory_limit_mb") == 0) {
            internal->limits.memory_limit_mb = atoi(value);
        }
    }
    
    fclose(file);
    return 0;
}
