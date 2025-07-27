#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process_handle_input.c
 * @brief Handle input processing for process command
 * @author XMD Team
 *
 * Processes input from file or stdin using XMD processor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../../include/main_internal.h"

/**
 * @brief Handle input processing for process command
 * @param processor XMD processor object
 * @param options Parsed command options
 * @return XMD result object or NULL on error
 */
xmd_result* cmd_process_handle_input(xmd_processor* processor, 
                                    const cmd_process_options_t* options) {
    if (!processor || !options) {
        return NULL;
    }
    
    bool use_stdin = (strcmp(options->input_file, "/dev/stdin") == 0);
    
    // Generate trace if requested (but not for stdin)
    if (options->trace_execution && !use_stdin) {
        // Create trace output filename
        char* trace_file = malloc(strlen(options->input_file) + 20);
        if (trace_file) {
            sprintf(trace_file, "%s.trace.log", options->input_file);
            // Note: In a real implementation, we'd enable trace logging here
            // For now, just print the trace filename that would be created
            if (options->debug_mode) {
                fprintf(stderr, "Debug: Trace would be written to %s\n", trace_file);
            }
            free(trace_file);
        }
    }
    
    xmd_result* result = NULL;
    
    // Process input
    if (use_stdin) {
        // Read from stdin into buffer
        size_t buffer_size = 4096;
        size_t total_size = 0;
        char* buffer = malloc(buffer_size);
        if (!buffer) {
            fprintf(stderr, "Error: Failed to allocate memory for stdin buffer\n");
            return NULL;
        }
        
        size_t bytes_read;
        while ((bytes_read = fread(buffer + total_size, 1, buffer_size - total_size - 1, stdin)) > 0) {
            total_size += bytes_read;
            
            // Expand buffer if needed
            if (total_size >= buffer_size - 1) {
                buffer_size *= 2;
                char* new_buffer = realloc(buffer, buffer_size);
                if (!new_buffer) {
                    fprintf(stderr, "Error: Failed to expand stdin buffer\n");
                    free(buffer);
                    return NULL;
                }
                buffer = new_buffer;
            }
        }
        
        buffer[total_size] = '\0';
        
        // Process string content
        result = xmd_process_string(processor, buffer, total_size);
        free(buffer);
    } else {
        // Process file normally
        result = xmd_process_file(processor, options->input_file);
    }
    
    return result;
}