/**
 * @file process_import.c
 * @brief Process import directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
    
    // Resolve relative path if needed
    char* resolved_path = NULL;
    if (trimmed_filename[0] != '/') {
        // Try multiple resolution strategies for relative paths
        
        // Strategy 1: Use source_file_path if available
        if (ctx->source_file_path) {
            char* source_dir = strdup(ctx->source_file_path);
            char* last_slash = strrchr(source_dir, '/');
            if (last_slash) {
                *last_slash = '\0'; // Remove filename, keep directory
                
                // Build resolved path: source_dir + "/" + trimmed_filename
                size_t resolved_len = strlen(source_dir) + strlen(trimmed_filename) + 2;
                resolved_path = malloc(resolved_len);
                if (resolved_path) {
                    snprintf(resolved_path, resolved_len, "%s/%s", source_dir, trimmed_filename);
                }
            }
            free(source_dir);
        }
        
        // Strategy 2: If source_file_path not available, try common patterns
        if (!resolved_path) {
            // Try looking for files in typical XMD project structure
            const char* common_paths[] = {
                ".xmd/src/principles/",
                "./",
                "../",
                NULL
            };
            
            for (int i = 0; common_paths[i] && !resolved_path; i++) {
                size_t resolved_len = strlen(common_paths[i]) + strlen(trimmed_filename) + 1;
                char* test_path = malloc(resolved_len);
                if (test_path) {
                    snprintf(test_path, resolved_len, "%s%s", common_paths[i], trimmed_filename);
                    
                    // Check if file exists
                    FILE* test_file = fopen(test_path, "r");
                    if (test_file) {
                        fclose(test_file);
                        resolved_path = test_path; // File found!
                    } else {
                        free(test_path);
                    }
                }
            }
        }
    }
    
    // Use resolved path if available, otherwise use original
    const char* import_path = resolved_path ? resolved_path : trimmed_filename;
    
    // Read and process the imported file
    FILE* file = fopen(import_path, "r");
    if (!file) {
        snprintf(output, output_size, "<!-- Error: Could not import file '%s' -->", import_path);
        free(filename);
        if (resolved_path) free(resolved_path);
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
    if (resolved_path) free(resolved_path);
    return 0;
}
