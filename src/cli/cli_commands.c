/**
 * @file cli_commands.c
 * @brief CLI command implementations for main.c compatibility
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cli.h"

// External function to get version
extern const char* xmd_get_version(void);

#define XMD_BUILD_DATE __DATE__

/**
 * @brief Process command implementation
 */
int cmd_process(int argc, char* argv[]) {
    // Default to stdin if no file specified
    const char* input_file = NULL;
    const char* output_file = NULL;
    bool verbose = false;
    
    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            }
        } else if (argv[i][0] != '-') {
            if (input_file == NULL) {
                input_file = argv[i];
            }
        }
    }
    
    return cli_process_file(input_file, output_file, verbose);
}

/**
 * @brief Validate command implementation
 */
int cmd_validate(int argc, char* argv[]) {
    const char* input_file = NULL;
    bool verbose = false;
    
    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (argv[i][0] != '-') {
            if (input_file == NULL) {
                input_file = argv[i];
            }
        }
    }
    
    if (input_file == NULL) {
        fprintf(stderr, "Error: validate command requires an input file\n");
        return 1;
    }
    
    return cli_validate_file(input_file, verbose);
}

/**
 * @brief Print usage information
 */
void print_usage(const char* program_name) {
    printf("Usage: %s <command> [options] [file]\n\n", program_name);
    printf("Commands:\n");
    printf("  process [file]     Process markdown file (default: stdin)\n");
    printf("  validate <file>    Validate markdown file syntax\n");
    printf("  upgrade           Upgrade to latest version\n");
    printf("  version           Show version information\n");
    printf("  help              Show this help message\n\n");
    printf("Options:\n");
    printf("  -v, --verbose     Enable verbose output\n");
    printf("  -o, --output      Specify output file\n\n");
    printf("Shorthand usage:\n");
    printf("  %s <file>         Same as '%s process <file>'\n", program_name, program_name);
    printf("  echo 'text' | %s  Process from stdin\n", program_name);
}

/**
 * @brief Print version information
 */
void print_version(void) {
    printf("XMD version %s\n", xmd_get_version());
    printf("Built on %s\n", XMD_BUILD_DATE);
}

/**
 * @brief Convert shorthand arguments to process command
 */
int convert_shorthand_to_process(int argc, char* argv[], int* new_argc, char*** new_argv) {
    // If first argument doesn't start with '-' and isn't a known command, treat as file
    const char* arg1 = argv[1];
    
    // Check if it's a known command
    if (strcmp(arg1, "process") == 0 || strcmp(arg1, "validate") == 0 || 
        strcmp(arg1, "upgrade") == 0 || strcmp(arg1, "version") == 0 || 
        strcmp(arg1, "help") == 0 || strcmp(arg1, "--help") == 0) {
        return -1; // Not shorthand
    }
    
    // Check if it starts with '-' (option)
    if (arg1[0] == '-') {
        return -1; // Not shorthand
    }
    
    // Convert to process command
    *new_argc = argc + 1;
    *new_argv = malloc((*new_argc) * sizeof(char*));
    if (*new_argv == NULL) {
        return -1;
    }
    
    (*new_argv)[0] = argv[0];
    (*new_argv)[1] = strdup("process");
    for (int i = 1; i < argc; i++) {
        (*new_argv)[i + 1] = strdup(argv[i]);
    }
    
    return 0;
}

/**
 * @brief Free converted argument vector
 */
void free_converted_argv(int argc, char** argv) {
    if (argv == NULL) return;
    
    // Free individual strings (except argv[0] which wasn't duplicated)
    for (int i = 1; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
}
