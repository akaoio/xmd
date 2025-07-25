/**
 * @file main.c
 * @brief XMD command-line interface main entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmd.h"
#include "variable.h"

/**
 * @brief Print usage information
 * @param program_name Name of the program
 */
static void print_usage(const char* program_name) {
    printf("XMD - eXtended MarkDown processor v%s\n\n", xmd_get_version());
    printf("Usage: %s <command> [options] <file>\n\n", program_name);
    printf("Commands:\n");
    printf("  process <file>     Process XMD file and output result\n");
    printf("  validate <file>    Validate XMD syntax without processing\n");
    printf("  version           Show version information\n");
    printf("  help              Show this help message\n\n");
    printf("Options:\n");
    printf("  -o, --output <file>   Output file (default: stdout)\n");
    printf("  -v, --variable <k=v>  Set variable (can be used multiple times)\n");
    printf("  --config <file>       Use configuration file\n");
    printf("  --debug               Enable debug mode\n");
    printf("  --trace               Enable execution tracing\n");
    printf("  --no-exec             Disable command execution\n");
    printf("  --format <fmt>        Output format: markdown, html, json\n");
    printf("\nExamples:\n");
    printf("  %s process input.md -o output.md\n", program_name);
    printf("  %s process template.md -v env=prod -v region=us-east\n", program_name);
    printf("  %s validate document.md\n", program_name);
}

/**
 * @brief Print version information
 */
static void print_version(void) {
    printf("XMD v%s\n", xmd_get_version());
    printf("eXtended MarkDown - Programmable markdown processor\n");
    printf("Copyright (c) 2024 XMD Project\n");
    printf("License: MIT\n");
}

/**
 * @brief Process command implementation
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
static int cmd_process(int argc, char* argv[]) {
    const char* input_file = NULL;
    const char* output_file = NULL;
    const char* config_file = NULL;
    const char* format = "markdown";
    bool debug_mode = false;
    bool trace_execution = false;
    bool allow_exec = true;
    
    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--variable") == 0) {
            if (i + 1 < argc) {
                // Parse variable in key=value format
                char* var_arg = argv[++i];
                char* eq = strchr(var_arg, '=');
                if (eq) {
                    *eq = '\0';
                    const char* key = var_arg;
                    const char* value = eq + 1;
                    
                    // For now, store as string variable (can be enhanced later for type detection)
                    variable* var = variable_create_string(value);
                    if (var) {
                        printf("Setting variable: %s = %s\n", key, value);
                        variable_unref(var); // Free since we're not storing it yet
                    }
                } else {
                    fprintf(stderr, "Error: Variable must be in key=value format\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "--config") == 0) {
            if (i + 1 < argc) {
                config_file = argv[++i];
            } else {
                fprintf(stderr, "Error: --config requires an argument\n");
                return 1;
            }
        } else if (strcmp(argv[i], "--debug") == 0) {
            debug_mode = true;
        } else if (strcmp(argv[i], "--trace") == 0) {
            trace_execution = true;
        } else if (strcmp(argv[i], "--no-exec") == 0) {
            allow_exec = false;
        } else if (strcmp(argv[i], "--format") == 0) {
            if (i + 1 < argc) {
                format = argv[++i];
            } else {
                fprintf(stderr, "Error: --format requires an argument\n");
                return 1;
            }
        } else if (argv[i][0] != '-') {
            if (input_file == NULL) {
                input_file = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            return 1;
        }
    }
    
    if (input_file == NULL) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    // Create configuration
    xmd_config* config = xmd_config_create_default();
    if (config == NULL) {
        fprintf(stderr, "Error: Failed to create configuration\n");
        return 1;
    }
    
    config->debug_mode = debug_mode;
    config->trace_execution = trace_execution;
    config->output_format = strdup(format);
    
    if (!allow_exec) {
        // Disable command execution by setting empty whitelist
        config->sandbox->exec_whitelist = calloc(1, sizeof(char*));
    }
    
    // Create processor
    xmd_processor* processor = xmd_processor_create(config);
    if (processor == NULL) {
        fprintf(stderr, "Error: Failed to create processor\n");
        xmd_config_free(config);
        return 1;
    }
    
    // Process file
    xmd_result* result = xmd_process_file(processor, input_file);
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to process file\n");
        xmd_processor_free(processor);
        xmd_config_free(config);
        return 1;
    }
    
    // Handle result
    if (result->error_code != XMD_SUCCESS) {
        fprintf(stderr, "Error: %s\n", result->error_message);
        xmd_result_free(result);
        xmd_processor_free(processor);
        xmd_config_free(config);
        return 1;
    }
    
    // Output result
    FILE* output = stdout;
    if (output_file != NULL) {
        output = fopen(output_file, "w");
        if (output == NULL) {
            fprintf(stderr, "Error: Cannot open output file %s\n", output_file);
            xmd_result_free(result);
            xmd_processor_free(processor);
            xmd_config_free(config);
            return 1;
        }
    }
    
    fprintf(output, "%s", result->output);
    
    if (output != stdout) {
        fclose(output);
    }
    
    // Print statistics in debug mode
    if (debug_mode) {
        fprintf(stderr, "Processing time: %llu ms\n", 
                (unsigned long long)result->processing_time_ms);
        fprintf(stderr, "Memory used: %llu bytes\n", 
                (unsigned long long)result->memory_used_bytes);
    }
    
    // Cleanup
    xmd_result_free(result);
    xmd_processor_free(processor);
    xmd_config_free(config);
    
    return 0;
}

/**
 * @brief Validate command implementation
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
static int cmd_validate(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    const char* input_file = argv[2];
    
    // Read file
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", input_file);
        return 1;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read content
    char* content = malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Error: Out of memory\n");
        fclose(file);
        return 1;
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    fclose(file);
    
    // Validate syntax
    xmd_error_code error = xmd_validate_syntax(content, bytes_read);
    free(content);
    
    if (error == XMD_SUCCESS) {
        printf("✓ Syntax is valid\n");
        return 0;
    } else {
        fprintf(stderr, "✗ Syntax error: %s\n", xmd_error_string(error));
        return 1;
    }
}

/**
 * @brief Main entry point
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    const char* command = argv[1];
    
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
        fprintf(stderr, "Error: Unknown command '%s'\n", command);
        print_usage(argv[0]);
        return 1;
    }
}