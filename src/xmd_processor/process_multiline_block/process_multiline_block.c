/**
 * @file process_multiline_block.c
 * @brief Multiline block processing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

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
                
                char directive_output[32768];  // Increased from 4096 to 32KB for long command outputs
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
