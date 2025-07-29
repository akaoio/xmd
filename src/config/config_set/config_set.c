#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file config_set.c
 * @brief Configuration value setter function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

// Global storage for configuration values (shared across config functions)
extern config_value* g_stored_values[100];
extern char* g_stored_keys[100];
extern size_t g_stored_count;

/**
 * @brief Set configuration value
 * @param config Configuration structure
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int config_set(xmd_config* config, const char* key, config_value* value) {
    if (!config || !key || !value) {
        return -1;
    }
    
    // Check if key already exists
    for (size_t i = 0; i < g_stored_count; i++) {
        if (g_stored_keys[i] && strcmp(g_stored_keys[i], key) == 0) {
            // Update existing value
            g_stored_values[i] = value;
            return 0;
        }
    }
    
    // Add new key-value pair
    if (g_stored_count < 100) {
        g_stored_keys[g_stored_count] = strdup(key);
        g_stored_values[g_stored_count] = value;
        g_stored_count++;
        return 0;
    }
    
    return -1; // No more space
}