#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process_create_config.c
 * @brief Create XMD configuration for process command
 * @author XMD Team
 *
 * Creates and configures the XMD configuration object.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/main_internal.h"

/**
 * @brief Create XMD configuration for process command
 * @param options Parsed command options
 * @return XMD configuration object or NULL on error
 */
xmd_config* cmd_process_create_config(const cmd_process_options_t* options) {
    if (!options) {
        return NULL;
    }
    
    // Create configuration
    xmd_config* config = xmd_config_create_default();
    if (config == NULL) {
        fprintf(stderr, "Error: Failed to create configuration\n");
        return NULL;
    }
    
    config->debug_mode = options->debug_mode;
    config->trace_execution = options->trace_execution;
    config->output_format = strdup(options->format);
    
    if (!options->allow_exec) {
        // Disable command execution by setting empty whitelist
        if (!config->sandbox) {
            // Create sandbox config if it doesn't exist
            config->sandbox = calloc(1, sizeof(xmd_sandbox_config));
        }
        if (config->sandbox) {
            config->sandbox->exec_whitelist = calloc(1, sizeof(char*));
        }
    }
    
    return config;
}