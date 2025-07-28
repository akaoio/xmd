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
 * @brief Check if multiline directive content contains script-like syntax
 */
static int contains_script_syntax(const char* directive_content) {
    // Look for for loops, += operators, + concatenation, or array literals
    return (strstr(directive_content, "for ") && strstr(directive_content, " in ")) ||
           strstr(directive_content, "+=") ||
           strstr(directive_content, " + ") ||  // String concatenation with +
           (strstr(directive_content, "[\"") && strstr(directive_content, "\"]"));
}

/**
 * @brief Enhanced multiline directive processor supporting all XMD directives
 * @param directive_content Content of the multiline directive
 * @param variables Variable store for processing
 * @param ctx Processor context for maintaining state (if NULL, creates temporary context)
 */
void process_multiline_directive_enhanced(const char* directive_content, store* variables, processor_context* ctx) {
    bool created_context = false;
    if (!ctx) {
        ctx = create_context(variables);
        created_context = true;
    }
    
    // Check if this contains advanced script syntax
    if (contains_script_syntax(directive_content)) {
        // Use the script block processor for complex syntax
        process_script_block(directive_content, variables);
        if (created_context) destroy_context(ctx);
        return;
    }
    
    char* content_copy = strdup(directive_content);
    char* line = strtok(content_copy, "\n\r");
    
    // Clear any previous multiline output
    variable* empty_var = variable_create_string("");
    if (empty_var) {
        store_set(variables, "_multiline_output", empty_var);
        variable_unref(empty_var);
    }
    
    char output_buffer[4096];
    size_t accumulated_output_len = 0;
    char* accumulated_output = malloc(8192);
    accumulated_output[0] = '\0';
    
    while (line) {
        char* trimmed = trim_whitespace(line);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            // Process XMD directive directly (single-line format)
            snprintf(output_buffer, sizeof(output_buffer), "%s", trimmed);
            
            // Use larger buffer for directive results
            size_t directive_buffer_size = 1024 * 1024;
            char* directive_result = malloc(directive_buffer_size);
            if (!directive_result) {
                line = strtok(NULL, "\n\r");
                continue;
            }
            
            int result = process_directive(output_buffer, ctx, directive_result, directive_buffer_size);
            
            // Accumulate any output from directives
            if (result == 0 && strlen(directive_result) > 0) {
                size_t result_len = strlen(directive_result);
                if (accumulated_output_len + result_len + 2 < 8192) {
                    if (accumulated_output_len > 0) {
                        strcat(accumulated_output, "\n");
                        accumulated_output_len++;
                    }
                    strcat(accumulated_output, directive_result);
                    accumulated_output_len += result_len;
                }
            }
            
            free(directive_result);
        } else if (strlen(trimmed) > 0) {
            // Process any XMD directive (not just 'set')
            snprintf(output_buffer, sizeof(output_buffer), "xmd:%s", trimmed);
            
            // Use larger buffer for directive results to avoid truncation
            size_t directive_buffer_size = 1024 * 1024;  // 1MB buffer for large outputs
            char* directive_result = malloc(directive_buffer_size);
            if (!directive_result) {
                continue;
            }
            
            int result = process_directive(output_buffer, ctx, directive_result, directive_buffer_size);
            
            // Accumulate any output from directives
            if (result == 0 && strlen(directive_result) > 0) {
                size_t result_len = strlen(directive_result);
                // Add space for newline if this isn't the first output
                size_t newline_space = (accumulated_output_len > 0) ? 1 : 0;
                size_t needed_size = accumulated_output_len + result_len + newline_space + 1;
                
                // Grow accumulated_output if needed
                if (needed_size > 8192) {
                    size_t new_size = needed_size + 1024;  // Add some extra space
                    char* new_buffer = realloc(accumulated_output, new_size);
                    if (new_buffer) {
                        accumulated_output = new_buffer;
                    }
                }
                
                // Add newline before output if there's already content
                if (accumulated_output_len > 0) {
                    strcat(accumulated_output, "\n");
                    accumulated_output_len += 1;
                }
                strcat(accumulated_output, directive_result);
                accumulated_output_len += result_len;
            }
            
            free(directive_result);
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
    free(content_copy);
    
    if (created_context) {
        destroy_context(ctx);
    }
}
