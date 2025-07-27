#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process_setup_processor.c
 * @brief Setup XMD processor with variables
 * @author XMD Team
 *
 * Creates XMD processor and sets command-line variables.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/main_internal.h"

/**
 * @brief Setup XMD processor with variables
 * @param config XMD configuration object
 * @param cmd_variables Array of command-line variables
 * @param var_count Number of variables
 * @return XMD processor object or NULL on error
 */
xmd_processor* cmd_process_setup_processor(xmd_config* config, 
                                          const cmd_variable_t cmd_variables[], 
                                          int var_count) {
    if (!config) {
        return NULL;
    }
    
    // Create processor
    xmd_processor* processor = xmd_processor_create(config);
    if (processor == NULL) {
        fprintf(stderr, "Error: Failed to create processor\n");
        return NULL;
    }
    
    // Set command-line variables in the processor
    for (int i = 0; i < var_count; i++) {
        if (cmd_variables[i].key && cmd_variables[i].value) {
            int result = xmd_set_variable(processor, cmd_variables[i].key, cmd_variables[i].value);
            if (result != 0) {
                fprintf(stderr, "Warning: Failed to set variable %s=%s\n", 
                        cmd_variables[i].key, cmd_variables[i].value);
            }
        }
    }
    
    return processor;
}