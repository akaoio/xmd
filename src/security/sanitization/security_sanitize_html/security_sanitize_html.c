/**
 * @file security_sanitize_html.c
 * @brief Sanitize HTML content
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security sanitization subsystem
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/utils.h"

// Forward declarations for utility functions - to be implemented
// static bool is_safe_html_tag(const char* tag);
// static size_t extract_tag_name(const char* tag_start, char* tag_name, size_t max_len);

// Stub implementation for process_html_tag
static size_t process_html_tag(const char* tag_content, char* output, 
                              size_t output_pos, size_t max_output_size) {
    (void)tag_content;
    (void)output;
    (void)max_output_size;
    return output_pos;  // For now, just return unchanged position
}
/**
 * @brief Sanitize HTML content
 * @param html HTML content to sanitize
 * @return Sanitized HTML (must be freed) or NULL on error
 */
char* security_sanitize_html(const char* html) {
    if (!html) {
        return NULL;
    }
    
    size_t input_len = strlen(html);
    char* result = xmd_malloc(input_len * 2 + 1); // Extra space for entity encoding
    if (!result) {
        return NULL;
    }
    
    size_t output_pos = 0;
    const char* p = html;
    
    while (*p && output_pos < input_len * 2 - 10) {
        if (*p == '<') {
            // Find end of tag
            const char* tag_end = strchr(p, '>');
            if (tag_end) {
                // Process the tag
                char tag_buffer[1024];
                size_t tag_size = tag_end - p + 1;
                if (tag_size < sizeof(tag_buffer)) {
                    memcpy(tag_buffer, p, tag_size);
                    tag_buffer[tag_size] = '\0';
                    
                    output_pos = process_html_tag(tag_buffer, result, output_pos, input_len * 2);
                }
                p = tag_end + 1;
            } else {
                // Incomplete tag, escape it
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&lt;");
                    output_pos += 4;
                }
                p++;
            }
        } else {
            // Regular character
            if (*p == '&') {
                if (output_pos + 5 < input_len * 2) {
                    strcpy(result + output_pos, "&amp;");
                    output_pos += 5;
                }
            } else if (*p == '>') {
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&gt;");
                    output_pos += 4;
                }
            } else if (*p >= 32 && *p < 127) {
                result[output_pos++] = *p;
            } else {
                // Replace non-printable with space
                result[output_pos++] = ' ';
            }
            p++;
        }
    }
    result[output_pos] = '\0';
    return result;
}
