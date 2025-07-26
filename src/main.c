/**
 * @file main.c
 * @brief XMD command-line interface main entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>  // for isatty
#include "xmd.h"
#include "variable.h"

/**
 * @brief Print usage information
 * @param program_name Name of the program
 */
static void print_usage(const char* program_name) {
    printf("XMD - eXtended MarkDown processor v%s\n\n", xmd_get_version());
    printf("Usage: %s <command> [options] <file>\n", program_name);
    printf("   or: <input> | %s <command> [options]\n", program_name);
    printf("   or: %s <input.md> [output.md]  (shorthand)\n\n", program_name);
    printf("Commands:\n");
    printf("  process <file>     Process XMD file and output result\n");
    printf("  process            Process XMD input from stdin (when piped)\n");
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
    printf("\nShorthand Examples:\n");
    printf("  %s input.md                    # Process input.md to stdout\n", program_name);
    printf("  %s input.md output.md          # Process input.md to output.md\n", program_name);
    printf("  echo \"{{name}}\" | %s            # Process stdin to stdout\n", program_name);
    printf("  echo \"{{name}}\" | %s out.md    # Process stdin to out.md\n", program_name);
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
 * @brief Cleanup function for command variables
 * @param cmd_variables Array of command variables
 * @param var_count Number of variables
 */
static void cleanup_cmd_variables(struct { char* key; char* value; } cmd_variables[], int var_count) {
    for (int i = 0; i < var_count; i++) {
        free(cmd_variables[i].key);
        free(cmd_variables[i].value);
    }
}

/**
 * @brief Format output according to specified format
 * @param content Raw processed content
 * @param format Output format ("markdown", "html", "json")
 * @param formatted_output Buffer to store formatted output
 * @param buffer_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int format_output(const char* content, const char* format, char* formatted_output, size_t buffer_size) {
    if (!content || !format || !formatted_output || buffer_size == 0) {
        return -1;
    }
    
    if (strcmp(format, "markdown") == 0) {
        // Markdown format - output as-is (default)
        if (strlen(content) >= buffer_size) {
            return -1;
        }
        strcpy(formatted_output, content);
        return 0;
    } 
    else if (strcmp(format, "html") == 0) {
        // HTML format - wrap in basic HTML structure and convert markdown
        int written = snprintf(formatted_output, buffer_size,
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <meta charset=\"UTF-8\">\n"
            "    <title>XMD Output</title>\n"
            "    <style>\n"
            "        body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; }\n"
            "        pre { background: #f5f5f5; padding: 1em; border-radius: 4px; }\n"
            "        code { background: #f0f0f0; padding: 2px 4px; border-radius: 2px; }\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "<div class=\"xmd-content\">\n"
            "%s\n"
            "</div>\n"
            "</body>\n"
            "</html>\n", 
            content);
        return (written < 0 || written >= buffer_size) ? -1 : 0;
    }
    else if (strcmp(format, "json") == 0) {
        // JSON format - wrap content in JSON structure
        // Escape quotes and newlines in content
        char escaped_content[buffer_size / 2];
        const char* src = content;
        char* dst = escaped_content;
        size_t remaining = sizeof(escaped_content) - 1;
        
        while (*src && remaining > 2) {
            if (*src == '"') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = '"';
                remaining -= 2;
            } else if (*src == '\\') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = '\\';
                remaining -= 2;
            } else if (*src == '\n') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 'n';
                remaining -= 2;
            } else if (*src == '\r') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 'r';
                remaining -= 2;
            } else if (*src == '\t') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 't';
                remaining -= 2;
            } else {
                *dst++ = *src;
                remaining--;
            }
            src++;
        }
        *dst = '\0';
        
        int written = snprintf(formatted_output, buffer_size,
            "{\n"
            "  \"status\": \"success\",\n"
            "  \"format\": \"json\",\n"
            "  \"processor\": \"XMD v%s\",\n"
            "  \"content\": \"%s\"\n"
            "}\n",
            xmd_get_version(), escaped_content);
        return (written < 0 || written >= buffer_size) ? -1 : 0;
    }
    
    return -1; // Unknown format
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
    
    // We'll store variables temporarily and set them on the processor later
    // Simple array to store key-value pairs
    struct {
        char* key;
        char* value;
    } cmd_variables[100]; // Max 100 variables
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
 * @brief Detect if argument looks like a file path
 * @param arg Argument to check
 * @return true if looks like file path, false otherwise
 */
static bool looks_like_file_path(const char* arg) {
    if (!arg) return false;
    
    // Check for common file extensions
    const char* dot = strrchr(arg, '.');
    if (dot) {
        const char* ext = dot + 1;
        if (strcmp(ext, "md") == 0 || strcmp(ext, "markdown") == 0 || 
            strcmp(ext, "txt") == 0 || strcmp(ext, "html") == 0 ||
            strcmp(ext, "json") == 0) {
            return true;
        }
    }
    
    // Check if contains path separators
    if (strchr(arg, '/') || strchr(arg, '\\')) {
        return true;
    }
    
    // Check if it's a simple filename without extension
    if (strlen(arg) > 0 && arg[0] != '-' && !strchr(arg, ' ') && 
        !strchr(arg, '\n') && !strchr(arg, '\t')) {
        return true;
    }
    
    return false;
}

/**
 * @brief Find the output file in arguments (looks for pattern: file.ext after input)
 * @param argc Argument count
 * @param argv Argument vector
 * @param start_idx Index to start searching from
 * @return Index of output file, or -1 if not found
 */
static int find_output_file_index(int argc, char* argv[], int start_idx) {
    // Look for a file that appears before any options (arguments starting with -)
    for (int i = start_idx; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Hit an option, stop looking
            break;
        }
        if (looks_like_file_path(argv[i])) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Convert shorthand arguments to full process command
 * @param argc Original argument count
 * @param argv Original argument vector
 * @param new_argc Pointer to store new argument count
 * @param new_argv Pointer to store new argument vector
 * @return 0 on success, -1 on error
 */
static int convert_shorthand_to_process(int argc, char* argv[], int* new_argc, char*** new_argv) {
    // Maximum possible arguments: original + "process" + "-o" + output
    char** processed_argv = malloc(sizeof(char*) * (argc + 4));
    if (!processed_argv) {
        return -1;
    }
    
    int processed_argc = 0;
    
    // Always keep program name
    processed_argv[processed_argc++] = argv[0];
    
    // Add "process" command
    processed_argv[processed_argc++] = strdup("process");
    
    // Analyze arguments to detect pattern
    // Only consider stdin available if it's actually piped (not interactive terminal)
    bool has_stdin = !isatty(STDIN_FILENO);
    bool first_is_file = (argc >= 2) ? looks_like_file_path(argv[1]) : false;
    
    // If first argument is a file, prioritize file processing over stdin
    if (first_is_file) {
        has_stdin = false;
    }
    
    
    if (argc == 1) {
        // Just "xmd" - if stdin available, process it
        if (has_stdin) {
            // xmd -> xmd process (stdin)
            *new_argc = processed_argc;
            *new_argv = processed_argv;
            return 0;
        } else {
            // Show usage
            free(processed_argv[1]);
            free(processed_argv);
            return -1;
        }
    } else if (has_stdin) {
        // Handle stdin patterns: echo "content" | xmd [output.md] [options...]
        if (first_is_file) {
            // echo "content" | xmd output.md [options...] -> xmd process -o output.md [options...]
            processed_argv[processed_argc++] = strdup("-o");
            processed_argv[processed_argc++] = strdup(argv[1]);
            
            // Add remaining arguments (options)
            for (int i = 2; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        } else {
            // echo "content" | xmd [options...] -> xmd process [options...]
            for (int i = 1; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        }
    } else if (first_is_file) {
        // Handle file input patterns: xmd input.md [output.md] [options...]
        processed_argv[processed_argc++] = strdup(argv[1]); // input file
        
        // Check for two-file pattern: xmd input.md output.md
        // Only if: argc == 3 AND second arg is file AND second arg doesn't start with -
        if (argc == 3 && 
            looks_like_file_path(argv[2]) && 
            argv[2][0] != '-') {
            // xmd input.md output.md -> xmd process input.md -o output.md
            processed_argv[processed_argc++] = strdup("-o");
            processed_argv[processed_argc++] = strdup(argv[2]);
        } else {
            // All other cases: xmd input.md [options...] 
            // Just pass through remaining arguments as-is
            for (int i = 2; i < argc; i++) {
                processed_argv[processed_argc++] = strdup(argv[i]);
            }
        }
    } else {
        // No recognizable pattern - pass through all arguments
        for (int i = 1; i < argc; i++) {
            processed_argv[processed_argc++] = strdup(argv[i]);
        }
    }
    
    *new_argc = processed_argc;
    *new_argv = processed_argv;
    return 0;
}

/**
 * @brief Free converted argument vector
 * @param argc Argument count
 * @param argv Argument vector to free
 */
static void free_converted_argv(int argc, char** argv) {
    for (int i = 1; i < argc; i++) { // Skip argv[0] as it's not duplicated
        free(argv[i]);
    }
    free(argv);
}

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