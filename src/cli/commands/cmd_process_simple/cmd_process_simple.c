/**
 * @file cmd_process_simple.c
 * @brief Simple XMD file processing command
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Extracted from: src/main.c
 */

#include <stdio.h>
#include <string.h>
#include "../../../../include/xmd.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Process an XMD file using the simple processing pipeline
 * @param filename Path to the XMD file to process
 * @return 0 on success, 1 on error
 */
int cmd_process_simple(const char* filename) {
    XMD_VALIDATE_PTRS(1, filename);
    
    printf("Processing XMD file: %s\n", filename);
    
    // Create default configuration
    xmd_config* config = NULL; // xmd_config_create_default(); // Commented out - function missing
    if (!config) {
        // fprintf(stderr, "Error: Failed to create default config\n");
        // return 1;
    }
    
    // Create processor with config
    xmd_processor* processor = xmd_processor_create(config);
    if (!processor) {
        fprintf(stderr, "Error: Failed to create processor\n");
        xmd_config_free(config);
        return 1;
    }
    
    // Process the file
    xmd_result* result = xmd_process_file(processor, filename);
    if (!result) {
        fprintf(stderr, "Error: Failed to process file '%s'\n", filename);
        xmd_processor_free(processor);
        xmd_config_free(config);
        return 1;
    }
    
    // Display output if successful
    if (result->error_code == XMD_SUCCESS) {
        if (result->output && strlen(result->output) > 0) {
            printf("%s", result->output);
            if (result->output[strlen(result->output) - 1] != '\n') {
                printf("\n");
            }
        }
    } else {
        fprintf(stderr, "Error: %s\n", result->error_message ? result->error_message : "Unknown error");
    }
    
    // Cleanup
    int exit_code = result->error_code == XMD_SUCCESS ? 0 : 1;
    xmd_result_free(result);
    xmd_processor_free(processor);
    xmd_config_free(config);
    
    return exit_code;
}
