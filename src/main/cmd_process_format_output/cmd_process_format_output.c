#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cmd_process_format_output.c
 * @brief Format and output result for process command
 * @author XMD Team
 *
 * Formats XMD result according to specified format and outputs it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/main_internal.h"

/**
 * @brief Format and output result for process command
 * @param result XMD result object
 * @param options Parsed command options
 * @return 0 on success, non-zero on error
 */
int cmd_process_format_output(const xmd_result* result, 
                             const cmd_process_options_t* options) {
    if (!result || !options) {
        return 1;
    }
    
    // Handle result
    if (result->error_code != XMD_SUCCESS) {
        fprintf(stderr, "Error: Processing failed with status %d\n", result->error_code);
        if (result->error_message) {
            fprintf(stderr, "Error message: %s\n", result->error_message);
        }
        return 1;
    }
    
    if (!result->output) {
        fprintf(stderr, "Error: No content generated\n");
        return 1;
    }
    
    // Output result
    FILE* output_stream = stdout;
    if (options->output_file && strcmp(options->output_file, "-") != 0) {
        output_stream = fopen(options->output_file, "w");
        if (!output_stream) {
            fprintf(stderr, "Error: Cannot open output file '%s'\n", options->output_file);
            return 1;
        }
    }
    
    // Format output according to specified format
    size_t content_len = strlen(result->output);
    char* formatted_output = malloc(content_len * 3 + 2000); // Extra space for formatting
    if (!formatted_output) {
        fprintf(stderr, "Error: Failed to allocate memory for formatting\n");
        if (output_stream != stdout) fclose(output_stream);
        return 1;
    }
    
    if (strcmp(options->format, "json") == 0) {
        // JSON format
        sprintf(formatted_output, 
                "{\n"
                "  \"status\": \"success\",\n"
                "  \"content\": \"");
        
        // Escape JSON content
        char* json_pos = formatted_output + strlen(formatted_output);
        for (size_t i = 0; i < content_len; i++) {
            char c = result->output[i];
            if (c == '"') {
                *json_pos++ = '\\';
                *json_pos++ = '"';
            } else if (c == '\\') {
                *json_pos++ = '\\';
                *json_pos++ = '\\';
            } else if (c == '\n') {
                *json_pos++ = '\\';
                *json_pos++ = 'n';
            } else if (c == '\r') {
                *json_pos++ = '\\';
                *json_pos++ = 'r';
            } else if (c == '\t') {
                *json_pos++ = '\\';
                *json_pos++ = 't';
            } else {
                *json_pos++ = c;
            }
        }
        
        sprintf(json_pos, "\"\n}\n");
    } else if (strcmp(options->format, "html") == 0) {
        // HTML format (basic wrapper)
        sprintf(formatted_output,
                "<!DOCTYPE html>\n"
                "<html>\n"
                "<head><title>XMD Output</title></head>\n"
                "<body>\n%s\n</body>\n"
                "</html>\n",
                result->output);
    } else {
        // Default: markdown or text format (no change)
        strcpy(formatted_output, result->output);
    }
    
    fprintf(output_stream, "%s", formatted_output);
    
    // Print statistics in debug mode
    if (options->debug_mode) {
        fprintf(stderr, "Debug: Processed %zu bytes, output %zu bytes\n", 
                content_len, strlen(formatted_output));
    }
    
    free(formatted_output);
    if (output_stream != stdout) {
        fclose(output_stream);
    }
    
    return 0;
}