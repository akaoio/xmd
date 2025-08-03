/**
 * @file main.c
 * @brief XMD main entry point - Genesis compliant (1 function only)
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Other functions moved to separate files following Genesis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations from separated files
extern void print_version(void);
extern void print_usage(const char* program_name);
extern int cmd_process_simple(const char* filename);

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
