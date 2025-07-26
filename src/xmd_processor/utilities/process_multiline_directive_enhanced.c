/**
 * @file process_multiline_directive_enhanced.c
 * @brief Enhanced multiline directive processing with full directive support
 * @author XMD Team
 * @date 2025-07-26
 */

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Enhanced multiline directive processor supporting all XMD directives
 * @param directive_content Content of the multiline directive
 * @param variables Variable store for processing
 */
void process_multiline_directive_enhanced(const char* directive_content, store* variables) {
    char* content_copy = strdup(directive_content);
    char* line = strtok(content_copy, "\n\r");
    
    processor_context* ctx = create_context(variables);
    char output_buffer[4096];
    size_t accumulated_output_len = 0;
    char* accumulated_output = malloc(8192);
    accumulated_output[0] = '\0';
    
    while (line) {
        char* trimmed = trim_whitespace(line);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            // Skip initial "xmd:" line
        } else if (strlen(trimmed) > 0) {
            // Process any XMD directive (not just 'set')
            snprintf(output_buffer, sizeof(output_buffer), "xmd:%s", trimmed);
            
            char directive_result[4096];
            int result = process_directive(output_buffer, ctx, directive_result, sizeof(directive_result));
            
            // Accumulate any output from directives
            if (result == 0 && strlen(directive_result) > 0) {
                size_t result_len = strlen(directive_result);
                if (accumulated_output_len + result_len + 1 >= 8192) {
                    accumulated_output = realloc(accumulated_output, accumulated_output_len + result_len + 1024);
                }
                strcat(accumulated_output, directive_result);
                accumulated_output_len += result_len;
            }
        }
        
        line = strtok(NULL, "\n\r");
    }
    
    // Store accumulated output in a special variable if any
    if (accumulated_output_len > 0) {
        variable* output_var = variable_create_string(accumulated_output);
        if (output_var) {
            store_set(variables, "_multiline_output", output_var);
            variable_unref(output_var);
        }
    }
    
    free(accumulated_output);
    free(ctx);
    free(content_copy);
}

/**
 * @brief Process a block of multiline XMD content with proper nesting support
 * @param content The multiline content to process
 * @param variables Variable store
 * @return Processed content (caller must free) or NULL on error
 */
char* process_multiline_block(const char* content, store* variables) {
    if (!content || !variables) return NULL;
    
    size_t content_len = strlen(content);
    size_t output_capacity = content_len * 2;
    char* output = malloc(output_capacity);
    size_t output_pos = 0;
    
    char* content_copy = strdup(content);
    char* line = strtok(content_copy, "\n\r");
    
    processor_context* ctx = create_context(variables);
    
    while (line) {
        char* trimmed = trim_whitespace(line);
        
        if (strlen(trimmed) > 0) {
            if (strncmp(trimmed, "xmd:", 4) == 0) {
                // Skip xmd: prefix lines
            } else {
                // Process as XMD directive
                char directive_line[512];
                snprintf(directive_line, sizeof(directive_line), "xmd:%s", trimmed);
                
                char directive_output[4096];
                process_directive(directive_line, ctx, directive_output, sizeof(directive_output));
                
                // Add output
                if (strlen(directive_output) > 0) {
                    size_t dir_len = strlen(directive_output);
                    if (output_pos + dir_len + 1 >= output_capacity) {
                        output_capacity = (output_pos + dir_len + 1000) * 2;
                        output = realloc(output, output_capacity);
                    }
                    memcpy(output + output_pos, directive_output, dir_len);
                    output_pos += dir_len;
                    output[output_pos++] = '\n';
                }
            }
        }
        
        line = strtok(NULL, "\n\r");
    }
    
    if (output_pos > 0 && output[output_pos - 1] == '\n') {
        output_pos--; // Remove trailing newline
    }
    output[output_pos] = '\0';
    
    free(content_copy);
    free(ctx);
    
    return output;
}
