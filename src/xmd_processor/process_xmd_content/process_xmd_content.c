/**
 * @file process_xmd_content.c
 * @brief Main XMD content processing implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Main XMD processing function
 * @param input Input markdown content with XMD directives
 * @param variables Variable store for XMD processing
 * @return Processed markdown content (caller must free) or NULL on error
 */
char* process_xmd_content(const char* input, store* variables) {
    if (!input || !variables) return NULL;
    
    processor_context* ctx = create_context(variables);
    
    size_t input_len = strlen(input);
    size_t output_capacity = input_len * 2;
    char* output = malloc(output_capacity);
    size_t output_pos = 0;
    
    const char* ptr = input;
    const char* input_end = input + input_len;
    
    while (ptr < input_end) {
        // Look for HTML comment start
        const char* comment_start = strstr(ptr, "<!--");
        
        if (!comment_start) {
            // No more comments, copy rest if executing
            if (should_execute_block(ctx)) {
                size_t remaining = input_end - ptr;
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before comment if executing
        if (should_execute_block(ctx)) {
            size_t before_len = comment_start - ptr;
            if (output_pos + before_len >= output_capacity) {
                output_capacity = (output_pos + before_len + 1000) * 2;
                output = realloc(output, output_capacity);
            }
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find comment end
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) {
            // Malformed comment, copy as-is if executing
            if (should_execute_block(ctx)) {
                size_t remaining = input_end - comment_start;
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Extract comment content
        size_t comment_content_len = comment_end - comment_start - 4;
        char* comment_content = malloc(comment_content_len + 1);
        strncpy(comment_content, comment_start + 4, comment_content_len);
        comment_content[comment_content_len] = '\0';
        
        // Check if this is an XMD directive
        char* trimmed = trim_whitespace(comment_content);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            // Process XMD directive
            if (is_multiline_directive(comment_content)) {
                process_multiline_directive_enhanced(comment_content, variables);
            } else {
                // Check if this is an exec directive - use dynamic allocation for it
                char* space = strchr(trimmed + 4, ' ');
                char command[64];
                char* args = "";
                
                if (space) {
                    size_t cmd_len = space - (trimmed + 4);
                    if (cmd_len >= sizeof(command)) cmd_len = sizeof(command) - 1;
                    strncpy(command, trimmed + 4, cmd_len);
                    command[cmd_len] = '\0';
                    args = trim_whitespace(space + 1);
                } else {
                    strncpy(command, trimmed + 4, sizeof(command) - 1);
                    command[sizeof(command) - 1] = '\0';
                }
                
                char* directive_output = NULL;
                
                if (strcmp(command, "exec") == 0) {
                    // Use dynamic allocation for exec commands
                    directive_output = process_exec_dynamic(args, ctx);
                } else {
                    // Use fixed buffer for other directives
                    char* fixed_buffer = malloc(65536);  // 64KB should be enough for non-exec directives
                    if (fixed_buffer) {
                        process_directive(trimmed, ctx, fixed_buffer, 65536);
                        directive_output = fixed_buffer;
                    }
                }
                
                // Add directive output if any
                if (directive_output && strlen(directive_output) > 0 && should_execute_block(ctx)) {
                    size_t dir_len = strlen(directive_output);
                    if (output_pos + dir_len >= output_capacity) {
                        output_capacity = (output_pos + dir_len + 1000) * 2;
                        output = realloc(output, output_capacity);
                    }
                    memcpy(output + output_pos, directive_output, dir_len);
                    output_pos += dir_len;
                }
                
                // Rule 14: Memory management - free allocated buffer
                if (directive_output) {
                    free(directive_output);
                }
            }
        } else {
            // Regular HTML comment, copy if executing
            if (should_execute_block(ctx)) {
                size_t comment_len = comment_end + 3 - comment_start;
                if (output_pos + comment_len >= output_capacity) {
                    output_capacity = (output_pos + comment_len + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, comment_len);
                output_pos += comment_len;
            }
        }
        
        free(comment_content);
        ptr = comment_end + 3;
    }
    
    output[output_pos] = '\0';
    
    // Substitute variables in final output
    char* final_output = substitute_variables(output, variables);
    
    free(output);
    free(ctx);
    
    return final_output;
}
