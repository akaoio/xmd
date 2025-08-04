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
#include "utils/common/common_macros.h"

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
    
    if (STR_EQUALS(command, "process")) {
        if (argc < 3) {
            XMD_ERROR_MSG("No file specified for processing");
            return 1;
        }
        return cmd_process_simple(argv[2]);
    } else if (STR_EQUALS(command, "version") || STR_EQUALS(command, "--version")) {
        print_version();
        return 0;
    } else if (STR_EQUALS(command, "help") || STR_EQUALS(command, "--help")) {
        print_usage(argv[0]);
        return 0;
    } else {
        XMD_ERROR_MSG("Unknown command '%s'", command);
        print_usage(argv[0]);
        return 1;
    }
}
