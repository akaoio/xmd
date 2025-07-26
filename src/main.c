/**
 * @file main.c
 * @brief XMD command-line interface main entry point
 */

#include "main_internal.h"
#include "xmd.h"
#include "variable.h"








/**
 * @brief Main entry point
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        // Check if stdin has content for shorthand: echo "content" | xmd
        if (!isatty(STDIN_FILENO)) {
            // Simulate: xmd process
            char* process_argv[] = { argv[0], "process" };
            return cmd_process(2, process_argv);
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }
    
    const char* command = argv[1];
    
    // Handle explicit commands first
    if (strcmp(command, "process") == 0) {
        return cmd_process(argc, argv);
    } else if (strcmp(command, "validate") == 0) {
        return cmd_validate(argc, argv);
    } else if (strcmp(command, "version") == 0) {
        print_version();
        return 0;
    } else if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    } else {
        // Try to detect shorthand patterns
        int new_argc;
        char** new_argv;
        
        if (convert_shorthand_to_process(argc, argv, &new_argc, &new_argv) == 0) {
            // Debug: print converted arguments
            if (getenv("XMD_DEBUG_SHORTHAND")) {
                fprintf(stderr, "Shorthand converted to: ");
                for (int i = 0; i < new_argc; i++) {
                    fprintf(stderr, "'%s' ", new_argv[i]);
                }
                fprintf(stderr, "\n");
            }
            int result = cmd_process(new_argc, new_argv);
            free_converted_argv(new_argc, new_argv);
            return result;
        } else {
            fprintf(stderr, "Error: Unknown command '%s'\n", command);
            print_usage(argv[0]);
            return 1;
        }
    }
}
