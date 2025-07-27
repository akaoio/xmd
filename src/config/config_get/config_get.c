/**
 * @file config_get.c
 * @brief Configuration value getter function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

// Global storage for configuration values (shared across config functions)
config_value* g_stored_values[100] = {0};
char* g_stored_keys[100] = {0};
size_t g_stored_count = 0;

/**
 * @brief Get configuration value
 * @param config Configuration structure
 * @param key Configuration key
 * @return Configuration value or NULL if not found
 */
config_value* config_get(xmd_config* config, const char* key) {
    if (!config || !key) {
        return NULL;
    }
    
    // For simplicity in this implementation, we'll use a linear search
    // In a production system, we'd use a hash table
    
    for (size_t i = 0; i < g_stored_count; i++) {
        if (g_stored_keys[i] && strcmp(g_stored_keys[i], key) == 0) {
            return g_stored_values[i];
        }
    }
    
    return NULL;
}