/**
 * @file process_import.c
 * @brief Process import directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process import directive
 * @param args Filename arguments for import directive
 * @param ctx Processor context
 * @param output Buffer to store imported content
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_import(const char* args, processor_context* ctx, char* output, size_t output_size) {
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Parse filename from args (remove quotes if present)
    char* filename = strdup(args);
    char* trimmed_filename = trim_whitespace(filename);
    
    // Remove quotes if present
    if (strlen(trimmed_filename) >= 2 &&
        ((trimmed_filename[0] == '"' && trimmed_filename[strlen(trimmed_filename)-1] == '"') ||
         (trimmed_filename[0] == '\'' && trimmed_filename[strlen(trimmed_filename)-1] == '\''))) {
        trimmed_filename[strlen(trimmed_filename)-1] = '\0';
        trimmed_filename++;
    }
    
    // Read and process the imported file
    FILE* file = fopen(trimmed_filename, "r");
    if (!file) {
        snprintf(output, output_size, "<!-- Error: Could not import file '%s' -->", trimmed_filename);
        free(filename);
        return 0;
    }
    
    // Read file content
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* file_content = malloc(file_size + 1);
    if (file_content) {
        size_t read_size = fread(file_content, 1, file_size, file);
        file_content[read_size] = '\0';
        
        // Process the imported content recursively
        char* processed_content = process_xmd_content(file_content, ctx->variables);
        if (processed_content) {
            strncpy(output, processed_content, output_size - 1);
            output[output_size - 1] = '\0';
            free(processed_content);
        }
        free(file_content);
    }
    
    fclose(file);
    free(filename);
    return 0;
}
