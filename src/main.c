/**
 * @file minimal_main.c
 * @brief Minimal XMD main with pure AST processing - Genesis compliant
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/xmd.h"

extern const char* xmd_get_version(void);

void print_version(void) {
    printf("XMD v%s\n", xmd_get_version());
    printf("eXtended MarkDown - Programmable markdown processor\n");
    printf("Copyright (c) 2024 XMD Project\n");
    printf("License: MIT\n");
}

void print_usage(const char* program_name) {
    printf("Usage: %s [command] [options] [file]\n", program_name);
    printf("Commands:\n");
    printf("  process <file>    Process XMD file using pure AST system\n");
    printf("  version           Show version information\n");
    printf("  help              Show this help message\n");
}

int cmd_process_simple(const char* filename) {
    printf("DEBUG: Starting cmd_process_simple with file: %s\n", filename);
    
    if (!filename) {
        fprintf(stderr, "Error: No file specified\n");
        return 1;
    }
    
    printf("DEBUG: Creating default config...\n");
    xmd_config* config = xmd_config_create_default();
    if (!config) {
        fprintf(stderr, "Error: Failed to create configuration\n");
        return 1;
    }
    printf("DEBUG: Config created successfully\n");
    
    printf("DEBUG: Creating processor...\n");
    xmd_processor* processor = xmd_processor_create(config);
    if (!processor) {
        fprintf(stderr, "Error: Failed to create processor\n");
        xmd_config_XMD_FREE_SAFE(config);
        return 1;
    }
    printf("DEBUG: Processor created successfully\n");
    
    printf("DEBUG: Processing file...\n");
    xmd_result* result = xmd_process_file(processor, filename);
    if (result) {
        printf("DEBUG: Processing completed, result exists\n");
        if (result->output) {
            printf("%s", result->output);
        }
        xmd_result_XMD_FREE_SAFE(result);
    } else {
        printf("DEBUG: Processing failed - result is NULL\n");
    }
    
    printf("DEBUG: Cleaning up...\n");
    xmd_processor_XMD_FREE_SAFE(processor);
    // Note: config is freed by xmd_processor_free, so don't free it again
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    const char* command = argv[1];
    
    if (strcmp(command, "process") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: No file specified for processing\n");
            return 1;
        }
        return cmd_process_simple(argv[2]);
    } else if (strcmp(command, "version") == 0 || strcmp(command, "--version") == 0) {
        print_version();
        return 0;
    } else if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    } else {
        fprintf(stderr, "Error: Unknown command '%s'\n", command);
        print_usage(argv[0]);
        return 1;
    }
}