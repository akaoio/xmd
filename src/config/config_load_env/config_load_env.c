#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file config_load_env.c
 * @brief Configuration environment loading function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

/**
 * @brief Load configuration from environment
 * @param config Configuration structure
 * @return 0 on success, -1 on error
 */
int config_load_env(xmd_config* config) {
    if (!config) {
        return -1;
    }
    
    // Load common environment variables
    const char* env_vars[][2] = {
        {"XMD_DEBUG", "debug"},
        {"XMD_VERBOSE", "verbose"},
        {"XMD_CONFIG", "config_file"},
        {"XMD_OUTPUT_FORMAT", "output_format"},
        {NULL, NULL}
    };
    
    for (int i = 0; env_vars[i][0]; i++) {
        const char* env_value = getenv(env_vars[i][0]);
        if (env_value) {
            config_value* value = malloc(sizeof(config_value));
            if (value) {
                value->type = CONFIG_STRING;
                value->data.string_val = strdup(env_value);
                config_set(config, env_vars[i][1], value);
            }
        }
    }
    
    return 0;
}