/**
 * @file security_sanitize_html.c
 * @brief Sanitize HTML content - Genesis compliant (1 function only)
 * @author XMD Development Team
 * @date 2025-08-04
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security sanitization subsystem
 * Helper function extracted to: ../process_html_tag/process_html_tag.c
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"
#include "../process_html_tag/process_html_tag.h"
/**
 * @brief Sanitize HTML content
 * @param html HTML content to sanitize
 * @return Sanitized HTML (must be freed) or NULL on error
 */
char* security_sanitize_html(const char* html) {
    XMD_VALIDATE_PTRS(NULL, html);
    
    size_t input_len = strlen(html);
    char* result;
    result = xmd_malloc(input_len * 2 + 1); // Extra space for entity encoding
    if (!result) return NULL;
    
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
                    memcpy(result + output_pos, "&lt;", 4);
                    output_pos += 4;
                }
                p++;
            }
        } else {
            // Regular character
            if (*p == '&') {
                if (output_pos + 5 < input_len * 2) {
                    memcpy(result + output_pos, "&amp;", 5);
                    output_pos += 5;
                }
            } else if (*p == '>') {
                if (output_pos + 4 < input_len * 2) {
                    memcpy(result + output_pos, "&gt;", 4);
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
