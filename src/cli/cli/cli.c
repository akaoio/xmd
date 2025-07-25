/**
 * @file cli.c
 * @brief Main CLI entry point and context management
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

#define XMD_VERSION "1.0.0"
#define XMD_BUILD_DATE __DATE__

/**
 * @brief Initialize CLI context
 * @param argc Argument count
 * @param argv Argument vector
 * @return CLI context or NULL on error
 */
cli_context* cli_init(int argc, char** argv) {
    if (argc < 1 || !argv) {
        return NULL;
    }
    
    cli_context* ctx = calloc(1, sizeof(cli_context));
    if (!ctx) {
        return NULL;
    }
    
    // Parse arguments
    ctx->args = cli_parse_args(argc, argv);
    if (!ctx->args) {
        free(ctx);
        return NULL;
    }
    
    // Store program name
    if (argv[0]) {
        ctx->program_name = strdup(argv[0]);
    }
    
    // Initialize XMD context (placeholder for now)
    ctx->xmd = NULL; // Will be initialized when needed
    ctx->exit_code = 0;
    
    return ctx;
}

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
            printf("Processing file: %s\n", ctx->args->input_file);
            if (ctx->args->output_file) {
                printf("Output file: %s\n", ctx->args->output_file);
            }
            // TODO: Implement actual processing
            return 0;
            
        case CLI_CMD_WATCH:
            if (!ctx->args->watch_directory) {
                fprintf(stderr, "Error: No directory specified for watching\n");
                return 1;
            }
            printf("Watching directory: %s\n", ctx->args->watch_directory);
            // TODO: Implement directory watching
            return 0;
            
        case CLI_CMD_VALIDATE:
            if (!ctx->args->input_file) {
                fprintf(stderr, "Error: No input file specified for validation\n");
                return 1;
            }
            printf("Validating file: %s\n", ctx->args->input_file);
            // TODO: Implement validation
            return 0;
            
        case CLI_CMD_CONFIG:
            printf("Current configuration:\n");
            // TODO: Implement config display
            return 0;
            
        case CLI_CMD_PLUGIN:
            if (!ctx->args->plugin_name) {
                fprintf(stderr, "Error: No plugin command specified\n");
                return 1;
            }
            printf("Plugin command: %s\n", ctx->args->plugin_name);
            // TODO: Implement plugin management
            return 0;
            
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

/**
 * @brief Show CLI help
 * @param program_name Program name
 */
void cli_show_help(const char* program_name) {
    const char* prog = program_name ? program_name : "xmd";
    
    printf("XMD - eXtended MarkDown Processor\n");
    printf("Usage: %s <command> [options]\n\n", prog);
    
    printf("Commands:\n");
    printf("  process <file>     Process a markdown file\n");
    printf("  watch <dir>        Watch directory for changes\n");
    printf("  validate <file>    Validate XMD syntax\n");
    printf("  config             Show configuration\n");
    printf("  plugin <cmd>       Plugin management\n");
    printf("  help               Show this help\n");
    printf("  version            Show version\n\n");
    
    printf("Options:\n");
    printf("  -o, --output <file>    Output file\n");
    printf("  -c, --config <file>    Configuration file\n");
    printf("  -v, --verbose          Verbose output\n");
    printf("  -q, --quiet            Quiet mode\n");
    printf("  -d, --debug            Debug mode\n");
    printf("  -h, --help             Show help\n");
    printf("      --version          Show version\n\n");
    
    printf("Examples:\n");
    printf("  %s process document.md\n", prog);
    printf("  %s process input.md -o output.md\n", prog);
    printf("  %s watch ./docs --verbose\n", prog);
    printf("  %s validate document.md\n", prog);
    printf("  %s plugin list\n", prog);
}

/**
 * @brief Show CLI version
 */
void cli_show_version(void) {
    printf("XMD version %s\n", XMD_VERSION);
    printf("Built on %s\n", XMD_BUILD_DATE);
}

/**
 * @brief Cleanup CLI context
 * @param ctx CLI context
 */
void cli_cleanup(cli_context* ctx) {
    if (!ctx) {
        return;
    }
    
    if (ctx->args) {
        free(ctx->args->input_file);
        free(ctx->args->output_file);
        free(ctx->args->config_file);
        free(ctx->args->plugin_name);
        free(ctx->args->watch_directory);
        free(ctx->args);
    }
    
    free(ctx->program_name);
    
    // Cleanup XMD context if initialized
    if (ctx->xmd) {
        // TODO: Cleanup XMD context
    }
    
    free(ctx);
}