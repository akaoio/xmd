/**
 * @file find_config_value.c
 * @brief Configuration value finder function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

// External global storage (defined in config_set.c)
extern char* g_stored_keys[100];
extern config_value* g_stored_values[100];  
extern size_t g_stored_count;

/**
 * @brief Find configuration value by key
 * @param config Configuration structure
 * @param key Configuration key
 * @return Index of value or -1 if not found
 */
int find_config_value(xmd_config* config, const char* key) {
    if (!config || !key) {
        return -1;
    }
    
    for (size_t i = 0; i < g_stored_count; i++) {
        // Search through configuration values
        if (g_stored_keys[i] && strcmp(g_stored_keys[i], key) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}