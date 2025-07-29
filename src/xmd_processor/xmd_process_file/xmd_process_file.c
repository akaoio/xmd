/**
 * @file xmd_process_file.c
 * @brief Main API file processor implementation
 * @author XMD Team
 */

#define _GNU_SOURCE  // For strdup
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/xmd.h"
#include "../../../include/cli.h"

/**
 * @brief Process file through XMD main API
 */
xmd_result* xmd_process_file(xmd_processor* processor, 
                             const char* input_path) {
    if (!processor || !input_path) {
        return NULL;
    }
    
    // Read file content
    FILE* file = fopen(input_path, "r");
    if (!file) {
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = -1;
            result->output = NULL;
            result->error_message = strdup("Failed to open file");
        }
        return result;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (size <= 0) {
        fclose(file);
        xmd_result* result = malloc(sizeof(xmd_result));
        if (result) {
            result->error_code = -1;
            result->output = NULL;
            result->error_message = strdup("Empty or invalid file");
        }
        return result;
    }
    
    // Read content
    char* content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    size_t read_size = fread(content, 1, size, file);
    content[read_size] = '\0';
    fclose(file);
    
    // Process using string processor
    xmd_result* result = xmd_process_string(processor, content, read_size);
    free(content);
    
    return result;
}