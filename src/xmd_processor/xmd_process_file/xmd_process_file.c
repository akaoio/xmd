/**
 * @file xmd_process_file.c
 * @brief Process XMD file with 2-parameter interface
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../../include/xmd_processor_internal.h"

// Global context functions
void xmd_set_current_file_path(const char* path);
void xmd_clear_current_file_path(void);

/**
 * @brief Process an XMD file
 * @param processor XMD processor instance
 * @param input_path Path to input file
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(xmd_processor* processor, const char* input_path) {
    if (!processor || !input_path) {
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = XMD_ERROR_INVALID_ARGUMENT;
            result->error_message = strdup("Invalid arguments: processor or input_path is NULL");
            result->output = NULL;
            result->output_length = 0;
            result->processing_time_ms = 0;
            result->memory_used_bytes = 0;
        }
        return result;
    }
    
    // Check if file exists
    struct stat st;
    if (stat(input_path, &st) != 0) {
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = XMD_ERROR_FILE_NOT_FOUND;
            char* error_msg = malloc(256);
            if (error_msg) {
                snprintf(error_msg, 256, "File not found: %s", input_path);
                result->error_message = error_msg;
            } else {
                result->error_message = strdup("File not found");
            }
            result->output = NULL;
            result->output_length = 0;
            result->processing_time_ms = 0;
            result->memory_used_bytes = 0;
        }
        return result;
    }
    
    // Read file contents
    FILE* file = fopen(input_path, "r");
    if (!file) {
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = XMD_ERROR_PERMISSION;
            char* error_msg = malloc(256);
            if (error_msg) {
                snprintf(error_msg, 256, "Cannot open file: %s", input_path);
                result->error_message = error_msg;
            } else {
                result->error_message = strdup("Cannot open file");
            }
            result->output = NULL;
            result->output_length = 0;
            result->processing_time_ms = 0;
            result->memory_used_bytes = 0;
        }
        return result;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate buffer for file contents
    char* content = malloc(file_size + 1);
    if (!content) {
        fclose(file);
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = XMD_ERROR_OUT_OF_MEMORY;
            result->error_message = strdup("Memory allocation failed");
            result->output = NULL;
            result->output_length = 0;
            result->processing_time_ms = 0;
            result->memory_used_bytes = 0;
        }
        return result;
    }
    
    // Read file contents
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    fclose(file);
    
    // Set the current file path for import resolution
    xmd_set_current_file_path(input_path);
    
    // Process the content using xmd_process_string
    xmd_result* result = xmd_process_string(processor, content, bytes_read);
    
    // Clear the file path
    xmd_clear_current_file_path();
    
    // Clean up
    free(content);
    
    return result;
}