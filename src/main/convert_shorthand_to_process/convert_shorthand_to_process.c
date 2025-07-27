#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file convert_shorthand_to_process.c
 * @brief Shorthand to process command conversion function
 * @author XMD Team
 *
 * Implementation of shorthand argument conversion for the XMD main module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/main_internal.h"

/**
 * @brief Convert shorthand arguments to full process command
 * @param argc Original argument count
 * @param argv Original argument vector
 * @param new_argc Pointer to store new argument count
 * @param new_argv Pointer to store new argument vector
 * @return 0 on success, -1 on error
 */
int convert_shorthand_to_process(int argc, char* argv[], int* new_argc, char*** new_argv) {
    // Maximum possible arguments: original + "process" + "-o" + output
    char** processed_argv = malloc(sizeof(char*) * (argc + 4));
    if (!processed_argv) {
        return -1;
    }
    
    int processed_argc = 0;
    
    // Always keep program name
    processed_argv[processed_argc++] = argv[0];
    
    // Add "process" command
    processed_argv[processed_argc++] = strdup("process");
    
    // Analyze arguments to detect pattern
    // Only consider stdin available if it's actually piped (not interactive terminal)
    bool has_stdin = !isatty(STDIN_FILENO);
    bool first_is_file = (argc >= 2) ? looks_like_file_path(argv[1]) : false;
    
    // If first argument is a file, prioritize file processing over stdin
    if (first_is_file) {
        has_stdin = false;
    }
    
    
    if (argc == 1) {
        // Just "xmd" - if stdin available, process it
        if (has_stdin) {
            // xmd -> xmd process (stdin)
            *new_argc = processed_argc;
            *new_argv = processed_argv;
            return 0;
        } else {
            // Show usage
            free(processed_argv[1]);
            free(processed_argv);
            return -1;
        }
    } else if (has_stdin) {
        // Handle stdin patterns: echo "content" | xmd [output.md] [options...]
        if (first_is_file) {
            // echo "content" | xmd output.md [options...] -> xmd process -o output.md [options...]
            processed_argv[processed_argc++] = strdup("-o");
            processed_argv[processed_argc++] = strdup(argv[1]);
            
            // Add remaining arguments (options)
            for (int i = 2; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        } else {
            // echo "content" | xmd [options...] -> xmd process [options...]
            for (int i = 1; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        }
    } else if (first_is_file) {
        // Handle file input patterns: xmd input.md [output.md] [options...]
        processed_argv[processed_argc++] = strdup(argv[1]); // input file
        
        // Check for two-file pattern: xmd input.md output.md
        // Only if: argc == 3 AND second arg is file AND second arg doesn't start with -
        if (argc == 3 && 
            looks_like_file_path(argv[2]) && 
            argv[2][0] != '-') {
            // xmd input.md output.md -> xmd process input.md -o output.md
            processed_argv[processed_argc++] = strdup("-o");
            processed_argv[processed_argc++] = strdup(argv[2]);
        } else {
            // All other cases: xmd input.md [options...] 
            // Just pass through remaining arguments as-is
            for (int i = 2; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        }
    } else {
        // No recognizable pattern - pass through all arguments
        for (int i = 1; i < argc; i++) {
            processed_argv[processed_argc++] = strdup(argv[i]);
        }
    }
    
    *new_argc = processed_argc;
    *new_argv = processed_argv;
    return 0;
}