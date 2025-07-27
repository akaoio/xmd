#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process_parse_args.c
 * @brief Parse command line arguments for process command
 * @author XMD Team
 *
 * Parses argc/argv for the process command and extracts options.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "../../../include/main_internal.h"

/**
 * @brief Parse command line arguments for process command
 * @param argc Argument count
 * @param argv Argument vector
 * @param options Output structure for parsed options
 * @param cmd_variables Array to store variables
 * @param var_count Pointer to variable count
 * @return 0 on success, non-zero on error
 */
int cmd_process_parse_args(int argc, char* argv[], cmd_process_options_t* options, 
                          cmd_variable_t cmd_variables[], int* var_count) {
    if (!options || !cmd_variables || !var_count) {
        return 1;
    }
    
    // Initialize options with defaults
    options->input_file = NULL;
    options->output_file = NULL;
    options->config_file = NULL;
    options->format = "markdown";
    options->debug_mode = false;
    options->trace_execution = false;
    options->allow_exec = true;
    *var_count = 0;
    
    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                options->output_file = argv[++i];
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--variable") == 0) {
            if (i + 1 < argc) {
                // Parse variable in key=value format
                char* var_arg = argv[++i];
                char* equals_pos = strchr(var_arg, '=');
                if (equals_pos == NULL) {
                    fprintf(stderr, "Error: Variable must be in key=value format\n");
                    return 1;
                }
                
                if (*var_count >= 100) {
                    fprintf(stderr, "Error: Too many variables (max 100)\n");
                    return 1;
                }
                
                // Store variable for later setting on processor
                *equals_pos = '\0';
                cmd_variables[*var_count].key = strdup(var_arg);
                cmd_variables[*var_count].value = strdup(equals_pos + 1);
                (*var_count)++;
                *equals_pos = '='; // Restore original string
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0) {
            if (i + 1 < argc) {
                options->config_file = argv[++i];
                // Validate config file exists
                FILE* test_file = fopen(options->config_file, "r");
                if (test_file == NULL) {
                    fprintf(stderr, "Error: Config file '%s' not found\n", options->config_file);
                    return 1;
                }
                fclose(test_file);
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--format") == 0) {
            if (i + 1 < argc) {
                options->format = argv[++i];
                // Validate format
                if (strcmp(options->format, "markdown") != 0 && 
                    strcmp(options->format, "html") != 0 && 
                    strcmp(options->format, "json") != 0 && 
                    strcmp(options->format, "text") != 0) {
                    fprintf(stderr, "Error: Unsupported format '%s'. Supported formats: markdown, html, json, text\n", 
                            options->format);
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            options->debug_mode = true;
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--trace") == 0) {
            options->trace_execution = true;
        } else if (strcmp(argv[i], "--no-exec") == 0) {
            options->allow_exec = false;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage("xmd");
            return 2; // Special return code for help
        } else if (strcmp(argv[i], "-") == 0) {
            // Handle stdin explicitly
            if (options->input_file == NULL) {
                options->input_file = "/dev/stdin";
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                return 1;
            }
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return 1;
        } else {
            // This should be the input file
            if (options->input_file == NULL) {
                options->input_file = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                return 1;
            }
        }
    }
    
    // If no input file specified, check if we should read from stdin
    if (options->input_file == NULL) {
        // Check if stdin has data (non-interactive)
        if (!isatty(STDIN_FILENO)) {
            options->input_file = "/dev/stdin";
        } else {
            fprintf(stderr, "Error: No input file specified\n");
            fprintf(stderr, "Usage: xmd process <file> [options]\n");
            fprintf(stderr, "   or: <command> | xmd process [options]  (pipe input)\n");
            return 1;
        }
    }
    
    return 0;
}