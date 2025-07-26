/**
 * @file cmd_process.c
 * @brief Process command implementation function
 * @author XMD Team
 *
 * Implementation of process command for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Process command implementation
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int cmd_process(int argc, char* argv[]) {
    const char* input_file = NULL;
    const char* output_file = NULL;
    const char* config_file = NULL;
    const char* format = "markdown";
    bool debug_mode = false;
    bool trace_execution = false;
    bool allow_exec = true;
    
    // We'll store variables temporarily and set them on the processor later
    // Simple array to store key-value pairs
    cmd_variable_t cmd_variables[100]; // Max 100 variables
    int var_count = 0;
    
    // Parse arguments
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                cleanup_cmd_variables(cmd_variables, var_count);
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
                    
                    // Store variable for later setting on processor
                    if (var_count < 100) {
                        cmd_variables[var_count].key = strdup(key);
                        cmd_variables[var_count].value = strdup(value);
                        var_count++;
                    } else {
                        fprintf(stderr, "Error: Too many variables (max 100)\n");
                        cleanup_cmd_variables(cmd_variables, var_count);
                        return 1;
                    }
                } else {
                    fprintf(stderr, "Error: Variable must be in key=value format\n");
                    cleanup_cmd_variables(cmd_variables, var_count);
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i]);
                cleanup_cmd_variables(cmd_variables, var_count);
                return 1;
            }
        } else if (strcmp(argv[i], "--config") == 0) {
            if (i + 1 < argc) {
                config_file = argv[++i];
                // Validate config file exists
                FILE* test_file = fopen(config_file, "r");
                if (!test_file) {
                    fprintf(stderr, "Error: Cannot open config file '%s'\n", config_file);
                    cleanup_cmd_variables(cmd_variables, var_count);
                    return 1;
                }
                fclose(test_file);
            } else {
                fprintf(stderr, "Error: --config requires an argument\n");
                cleanup_cmd_variables(cmd_variables, var_count);
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
                // Validate format
                if (strcmp(format, "markdown") != 0 && 
                    strcmp(format, "html") != 0 && 
                    strcmp(format, "json") != 0) {
                    fprintf(stderr, "Error: Invalid format '%s'. Valid formats: markdown, html, json\n", format);
                    cleanup_cmd_variables(cmd_variables, var_count);
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: --format requires an argument\n");
                cleanup_cmd_variables(cmd_variables, var_count);
                return 1;
            }
        } else if (argv[i][0] != '-') {
            if (input_file == NULL) {
                input_file = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                cleanup_cmd_variables(cmd_variables, var_count);
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            cleanup_cmd_variables(cmd_variables, var_count);
            return 1;
        }
    }
    
    // If no input file specified, check if we should read from stdin
    bool use_stdin = false;
    if (input_file == NULL) {
        // Check if stdin has data (non-interactive)
        if (!isatty(STDIN_FILENO)) {
            use_stdin = true;
            input_file = "/dev/stdin";
        } else {
            fprintf(stderr, "Error: No input file specified\n");
            fprintf(stderr, "Usage: xmd process <file> [options]\n");
            fprintf(stderr, "   or: <command> | xmd process [options]  (pipe input)\n");
            cleanup_cmd_variables(cmd_variables, var_count);
            return 1;
        }
    }
    
    // Create configuration
    xmd_config* config = xmd_config_create_default();
    if (config == NULL) {
        fprintf(stderr, "Error: Failed to create configuration\n");
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    config->debug_mode = debug_mode;
    config->trace_execution = trace_execution;
    config->output_format = strdup(format);
    
    if (!allow_exec) {
        // Disable command execution by setting empty whitelist
        if (!config->sandbox) {
            // Create sandbox config if it doesn't exist
            config->sandbox = calloc(1, sizeof(xmd_sandbox_config));
        }
        if (config->sandbox) {
            config->sandbox->exec_whitelist = calloc(1, sizeof(char*));
        }
    }
    
    // Create processor
    xmd_processor* processor = xmd_processor_create(config);
    if (processor == NULL) {
        fprintf(stderr, "Error: Failed to create processor\n");
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Set command-line variables in the processor
    for (int i = 0; i < var_count; i++) {
        xmd_error_code err = xmd_set_variable(processor, cmd_variables[i].key, cmd_variables[i].value);
        if (err != XMD_SUCCESS) {
            fprintf(stderr, "Warning: Failed to set variable %s\n", cmd_variables[i].key);
        }
    }
    
    // Generate trace if requested (but not for stdin)
    if (trace_execution && !use_stdin) {
        // Create trace output filename
        char trace_filename[512];
        if (output_file) {
            snprintf(trace_filename, sizeof(trace_filename), "%s.trace", output_file);
        } else {
            snprintf(trace_filename, sizeof(trace_filename), "%s.trace", input_file);
        }
        
        int trace_result = debugger_trace(input_file, trace_filename);
        if (trace_result != 0) {
            fprintf(stderr, "Warning: Failed to generate trace file\n");
        }
    }
    
    // Process input
    xmd_result* result = NULL;
    if (use_stdin) {
        // Read from stdin into buffer
        char* stdin_content = NULL;
        size_t stdin_size = 0;
        size_t stdin_capacity = 4096;
        
        stdin_content = malloc(stdin_capacity);
        if (!stdin_content) {
            fprintf(stderr, "Error: Memory allocation failed for stdin\n");
            xmd_processor_free(processor);
            xmd_config_free(config);
            cleanup_cmd_variables(cmd_variables, var_count);
            return 1;
        }
        
        // Read all input from stdin
        int c;
        while ((c = getchar()) != EOF) {
            if (stdin_size >= stdin_capacity - 1) {
                stdin_capacity *= 2;
                char* new_content = realloc(stdin_content, stdin_capacity);
                if (!new_content) {
                    fprintf(stderr, "Error: Memory reallocation failed\n");
                    free(stdin_content);
                    xmd_processor_free(processor);
                    xmd_config_free(config);
                    cleanup_cmd_variables(cmd_variables, var_count);
                    return 1;
                }
                stdin_content = new_content;
            }
            stdin_content[stdin_size++] = c;
        }
        stdin_content[stdin_size] = '\0';
        
        // Process string content
        result = xmd_process_string(processor, stdin_content, stdin_size);
        free(stdin_content);
    } else {
        // Process file normally
        result = xmd_process_file(processor, input_file);
    }
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to process file\n");
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    // Handle result
    if (result->error_code != XMD_SUCCESS) {
        fprintf(stderr, "Error: %s\n", result->error_message);
        xmd_result_free(result);
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
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
            cleanup_cmd_variables(cmd_variables, var_count);
            return 1;
        }
    }
    
    // Format output according to specified format
    size_t content_len = result->output_length;
    char* formatted_output = malloc(content_len * 3 + 2000); // Extra space for formatting
    if (!formatted_output) {
        fprintf(stderr, "Error: Memory allocation failed for output formatting\n");
        if (output != stdout) {
            fclose(output);
        }
        xmd_result_free(result);
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    if (format_output(result->output, format, formatted_output, content_len * 3 + 2000) != 0) {
        fprintf(stderr, "Error: Failed to format output\n");
        free(formatted_output);
        if (output != stdout) {
            fclose(output);
        }
        xmd_result_free(result);
        xmd_processor_free(processor);
        xmd_config_free(config);
        cleanup_cmd_variables(cmd_variables, var_count);
        return 1;
    }
    
    fprintf(output, "%s", formatted_output);
    free(formatted_output);
    
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
    cleanup_cmd_variables(cmd_variables, var_count);
    
    return 0;
}
