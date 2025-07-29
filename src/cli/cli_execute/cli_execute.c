/**
 * @file cli_execute.c
 * @brief CLI command execution function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/cli.h"

// Forward declaration
int cmd_watch(int argc, char* argv[]);

/**
 * @brief Execute CLI command
 * @param ctx CLI context
 * @return Exit code
 */
int cli_execute(cli_context* ctx) {
    if (!ctx || !ctx->args) {
        return 1;
    }
    
    // Handle help and version first
    if (ctx->args->help) {
        cli_show_help(ctx->program_name);
        return 0;
    }
    
    if (ctx->args->version) {
        cli_show_version();
        return 0;
    }
    
    // Execute command based on type
    switch (ctx->args->command) {
        case CLI_CMD_PROCESS:
            if (!ctx->args->input_file) {
                fprintf(stderr, "Error: No input file specified\n");
                return 1;
            }
            return cli_process_file(ctx->args->input_file, ctx->args->output_file, ctx->args->verbose);
            
        case CLI_CMD_WATCH:
            // Route to the new cmd_watch function which supports both files and directories
            // Convert CLI arguments to match cmd_watch expectations
            {
                char* watch_argv[8];
                int watch_argc = 0;
                
                watch_argv[watch_argc++] = "xmd";
                watch_argv[watch_argc++] = "watch";
                
                if (ctx->args->watch_directory) {
                    watch_argv[watch_argc++] = ctx->args->watch_directory;
                }
                
                if (ctx->args->output_file) {
                    watch_argv[watch_argc++] = ctx->args->output_file;
                }
                
                if (ctx->args->verbose) {
                    watch_argv[watch_argc++] = "--verbose";
                }
                
                // Call the new unified watch command
                return cmd_watch(watch_argc, watch_argv);
            }
            
        case CLI_CMD_VALIDATE:
            if (!ctx->args->input_file) {
                fprintf(stderr, "Error: No input file specified for validation\n");
                return 1;
            }
            return cli_validate_file(ctx->args->input_file, ctx->args->verbose);
            
        case CLI_CMD_CONFIG:
            return cli_show_config(ctx->args->config_file);
            
        case CLI_CMD_HELP:
            cli_show_help(ctx->program_name);
            return 0;
            
        case CLI_CMD_VERSION:
            cli_show_version();
            return 0;
            
        default:
            fprintf(stderr, "Error: Unknown command\n");
            return 1;
    }
}