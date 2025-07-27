#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process.c
 * @brief Process command implementation function
 * @author XMD Team
 *
 * Implementation of process command for the XMD main module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/main_internal.h"

/**
 * @brief Process command implementation
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int cmd_process(int argc, char* argv[]) {
    cmd_process_options_t options;
    cmd_variable_t cmd_variables[100]; // Max 100 variables
    int var_count = 0;
    
    // Parse command line arguments
    int parse_result = cmd_process_parse_args(argc, argv, &options, cmd_variables, &var_count);
    if (parse_result != 0) {
        cleanup_cmd_variables(cmd_variables, var_count);
        return (parse_result == 2) ? 0 : 1; // Help returns 0, errors return 1
    }
    
    // Create configuration
    xmd_config* config = cmd_process_create_config(&options);
    if (!config) {
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Setup processor with variables
    xmd_processor* processor = cmd_process_setup_processor(config, cmd_variables, var_count);
    if (!processor) {
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Process input
    xmd_result* result = cmd_process_handle_input(processor, &options);
    if (!result) {
        fprintf(stderr, "Error: Processing failed\n");
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Format and output result
    int output_result = cmd_process_format_output(result, &options);
    if (output_result != 0) {
        xmd_result_free(result);
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Cleanup
    xmd_result_free(result);
    xmd_processor_free(processor);
    xmd_config_free(config);
    cleanup_cmd_variables(cmd_variables, var_count);
    
    return 0;
}