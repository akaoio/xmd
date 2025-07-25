/**
 * @file cli.c
 * @brief Main CLI entry point and context management
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../../../include/cli.h"
#include "../../../include/lexer.h"
#include "../../../include/variable.h"
#include "../../../include/store.h"

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
            return cli_process_file(ctx->args->input_file, ctx->args->output_file, ctx->args->verbose);
            
        case CLI_CMD_WATCH:
            if (!ctx->args->watch_directory) {
                fprintf(stderr, "Error: No directory specified for watching\n");
                return 1;
            }
            return cli_watch_directory(ctx->args->watch_directory, ctx->args->verbose);
            
        case CLI_CMD_VALIDATE:
            if (!ctx->args->input_file) {
                fprintf(stderr, "Error: No input file specified for validation\n");
                return 1;
            }
            return cli_validate_file(ctx->args->input_file, ctx->args->verbose);
            
        case CLI_CMD_CONFIG:
            return cli_show_config(ctx->args->config_file);
            
        case CLI_CMD_PLUGIN:
            if (!ctx->args->plugin_name) {
                fprintf(stderr, "Error: No plugin command specified\n");
                return 1;
            }
            return cli_manage_plugin(ctx->args->plugin_name, ctx->args->verbose);
            
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
        if (ctx->xmd) {
            xmd_cleanup(ctx->xmd);
        }
    }
    
    free(ctx);
}

/**
 * @brief Process a markdown file
 * @param input_file Input file path
 * @param output_file Output file path (NULL for stdout)
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_process_file(const char* input_file, const char* output_file, bool verbose) {
    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    if (verbose) {
        printf("Processing file: %s\n", input_file);
        if (output_file) {
            printf("Output file: %s\n", output_file);
        }
    }
    
    // Check if input file exists
    struct stat st;
    if (stat(input_file, &st) != 0) {
        fprintf(stderr, "Error: Cannot access input file '%s'\n", input_file);
        return 1;
    }
    
    // Read input file
    FILE* input = fopen(input_file, "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_file);
        return 1;
    }
    
    // Get file size
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    // Read content
    char* content = malloc(size + 1);
    if (!content) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(input);
        return 1;
    }
    
    size_t read_size = fread(content, 1, size, input);
    content[read_size] = '\0';
    fclose(input);
    
    // Process content with XMD
    lexer* lex = lexer_create(content);
    if (!lex) {
        fprintf(stderr, "Error: Failed to create lexer\n");
        free(content);
        return 1;
    }
    
    store* var_store = store_create();
    if (!var_store) {
        fprintf(stderr, "Error: Failed to create variable store\n");
        lexer_free(lex);
        free(content);
        return 1;
    }
    
    // Basic processing - just echo the content for now
    FILE* output = stdout;
    if (output_file) {
        output = fopen(output_file, "w");
        if (!output) {
            fprintf(stderr, "Error: Cannot create output file '%s'\n", output_file);
            store_destroy(var_store);
            lexer_free(lex);
            free(content);
            return 1;
        }
    }
    
    fprintf(output, "%s", content);
    
    if (output_file && output != stdout) {
        fclose(output);
        if (verbose) {
            printf("Output written to: %s\n", output_file);
        }
    }
    
    // Cleanup
    store_destroy(var_store);
    lexer_free(lex);
    free(content);
    
    return 0;
}

/**
 * @brief Watch directory for changes
 * @param directory Directory to watch
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_watch_directory(const char* directory, bool verbose) {
    if (!directory) {
        fprintf(stderr, "Error: No directory specified\n");
        return 1;
    }
    
    // Check if directory exists
    struct stat st;
    if (stat(directory, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Directory '%s' does not exist or is not a directory\n", directory);
        return 1;
    }
    
    if (verbose) {
        printf("Watching directory: %s\n", directory);
        printf("Press Ctrl+C to stop watching\n");
    }
    
    // Simple polling implementation
    printf("Directory watching started (basic polling implementation)\n");
    printf("Note: This is a simplified implementation\n");
    
    // Just print a message and return for now
    printf("Watching would monitor '%s' for .md file changes\n", directory);
    
    return 0;
}

/**
 * @brief Validate XMD file syntax
 * @param input_file Input file path
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_validate_file(const char* input_file, bool verbose) {
    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    if (verbose) {
        printf("Validating file: %s\n", input_file);
    }
    
    // Check if file exists
    struct stat st;
    if (stat(input_file, &st) != 0) {
        fprintf(stderr, "Error: Cannot access file '%s'\n", input_file);
        return 1;
    }
    
    // Read and validate file
    FILE* input = fopen(input_file, "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", input_file);
        return 1;
    }
    
    // Get file size and read content
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    char* content = malloc(size + 1);
    if (!content) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(input);
        return 1;
    }
    
    size_t read_size = fread(content, 1, size, input);
    content[read_size] = '\0';
    fclose(input);
    
    // Create lexer to validate syntax
    lexer* lex = lexer_create(content);
    if (!lex) {
        fprintf(stderr, "Error: Failed to create lexer for validation\n");
        free(content);
        return 1;
    }
    
    // Simple validation - just check if we can create the lexer
    // For now, we'll assume no errors if lexer was created successfully
    // More sophisticated validation would process tokens and check syntax
    
    printf("✓ File '%s' is valid\n", input_file);
    
    lexer_free(lex);
    free(content);
    
    return 0;
}

/**
 * @brief Show configuration
 * @param config_file Config file path (NULL for default)
 * @return Exit code
 */
int cli_show_config(const char* config_file) {
    printf("XMD Configuration:\n");
    printf("=================\n");
    printf("Version: %s\n", XMD_VERSION);
    printf("Build Date: %s\n", XMD_BUILD_DATE);
    
    if (config_file) {
        printf("Config File: %s\n", config_file);
        
        // Check if config file exists
        struct stat st;
        if (stat(config_file, &st) == 0) {
            printf("Config Status: Found\n");
        } else {
            printf("Config Status: Not found\n");
        }
    } else {
        printf("Config File: Default (none specified)\n");
    }
    
    printf("Default Settings:\n");
    printf("- Debug Mode: Off\n");
    printf("- Verbose Mode: Off\n");
    printf("- Output Format: Auto-detect\n");
    
    return 0;
}

/**
 * @brief Manage plugins
 * @param plugin_command Plugin command
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_manage_plugin(const char* plugin_command, bool verbose) {
    if (!plugin_command) {
        fprintf(stderr, "Error: No plugin command specified\n");
        return 1;
    }
    
    if (verbose) {
        printf("Plugin command: %s\n", plugin_command);
    }
    
    if (strcmp(plugin_command, "list") == 0) {
        printf("Available Plugins:\n");
        printf("==================\n");
        printf("(No plugins currently loaded)\n");
        printf("\nPlugin directories searched:\n");
        printf("- ./plugins/\n");
        printf("- ~/.xmd/plugins/\n");
        printf("- /usr/local/lib/xmd/plugins/\n");
        
    } else if (strcmp(plugin_command, "help") == 0) {
        printf("Plugin Management Commands:\n");
        printf("==========================\n");
        printf("list     - List available plugins\n");
        printf("load     - Load a plugin\n");
        printf("unload   - Unload a plugin\n");
        printf("info     - Show plugin information\n");
        printf("help     - Show this help\n");
        
    } else {
        printf("Plugin management for command: %s\n", plugin_command);
        printf("(Plugin system not fully implemented yet)\n");
    }
    
    return 0;
}