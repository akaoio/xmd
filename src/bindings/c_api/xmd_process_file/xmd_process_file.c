/**
 * @file xmd_process_file.c
 * @brief XMD file processing function
 * @author XMD Team
 *
 * Implementation of XMD file processing for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Process markdown file
 * @param handle XMD context handle
 * @param input_path Input file path
 * @param output_path Output file path (optional)
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(void* handle, const char* input_path, const char* output_path) {
    if (!handle || !input_path) {
        return NULL; // Return NULL for invalid parameters
    }
    
    // Set the current file path for import resolution
    extern void xmd_set_current_file_path(const char* path);
    extern void xmd_clear_current_file_path(void);
    xmd_set_current_file_path(input_path);
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Read input file
    FILE* input_file = fopen(input_path, "r");
    if (!input_file) {
        return create_result(-1, NULL, "Failed to open input file");
    }
    
    // Get file size
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(input_file);
        return create_result(-1, NULL, "Failed to get file size");
    }
    
    // Read file content
    char* content = malloc(file_size + 1);
    if (!content) {
        fclose(input_file);
        return create_result(-1, NULL, "Memory allocation failed");
    }
    
    size_t bytes_read = fread(content, 1, file_size, input_file);
    content[bytes_read] = '\0';
    fclose(input_file);
    
    // Process the content
    xmd_result* result = xmd_process_string_api(handle, content, bytes_read);
    
    // Write output file if specified
    if (output_path && result && result->error_code == 0) {
        FILE* output_file = fopen(output_path, "w");
        if (output_file) {
            fwrite(result->output, 1, result->output_length, output_file);
            fclose(output_file);
        }
    }
    
    free(content);
    
    // Clear the file path after processing
    xmd_clear_current_file_path();
    
    return result;
}
