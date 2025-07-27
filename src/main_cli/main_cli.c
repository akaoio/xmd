/**
 * @file main_cli.c
 * @brief Main CLI executable entry point
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/cli.h"

/**
 * @brief Main entry point for XMD CLI
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int main(int argc, char** argv) {
    // Initialize CLI context
    cli_context* ctx = cli_init(argc, argv);
    if (!ctx) {
        fprintf(stderr, "Error: Failed to initialize CLI\n");
        return 1;
    }
    
    // Execute the command
    int exit_code = cli_execute(ctx);
    
    // Cleanup
    cli_cleanup(ctx);
    
    return exit_code;
}
