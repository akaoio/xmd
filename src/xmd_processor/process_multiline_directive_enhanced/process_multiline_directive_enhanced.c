/**
 * @file process_multiline_directive_enhanced.c
 * @brief Enhanced multiline directive processing with full directive support
 * @author XMD Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

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
            
            char directive_result[32768];  // Increased from 4096 to 32KB for long command outputs
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
