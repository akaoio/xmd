/**
 * @file process_html_tag.c
 * @brief Process HTML tag for sanitization - Genesis compliant extraction
 * @author XMD Development Team
 * @date 2025-08-04
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Extracted from: security_sanitize_html.c for Genesis compliance
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Process HTML tag using whitelist approach
 * @param tag_content The HTML tag content to process
 * @param output Output buffer to write sanitized content
 * @param output_pos Current position in output buffer
 * @param max_output_size Maximum size of output buffer
 * @return New position in output buffer after processing
 */
size_t process_html_tag(const char* tag_content, char* output, 
                       size_t output_pos, size_t max_output_size) {
    // Whitelist of safe HTML tags (read-only tags for display)
    static const char* safe_tags[] = {
        "p", "br", "strong", "em", "i", "b", "u", "h1", "h2", "h3", "h4", "h5", "h6",
        "ul", "ol", "li", "div", "span", "blockquote", "code", "pre", NULL
    };
    
    // Extract tag name
    const char* tag_start = tag_content;
    if (*tag_start == '<') tag_start++;
    
    // Skip whitespace
    while (*tag_start && (*tag_start == ' ' || *tag_start == '\t')) tag_start++;
    
    // Find end of tag name
    const char* tag_end = tag_start;
    while (*tag_end && *tag_end != ' ' && *tag_end != '>' && *tag_end != '/') tag_end++;
    
    size_t tag_len = tag_end - tag_start;
    if (tag_len == 0 || tag_len > 20) {
        // Invalid or suspicious tag - escape it
        size_t remaining = max_output_size - output_pos;
        if (remaining >= 4) {
            memcpy(output + output_pos, "&lt;", 4);
            return output_pos + 4;
        }
        return output_pos;
    }
    
    // Check if tag is in whitelist
    char tag_name[32];
    if (tag_len < sizeof(tag_name)) {
        strncpy(tag_name, tag_start, tag_len);
        tag_name[tag_len] = '\0';
        
        // Convert to lowercase for comparison
        for (size_t i = 0; i < tag_len; i++) {
            if (tag_name[i] >= 'A' && tag_name[i] <= 'Z') {
                tag_name[i] += 32;
            }
        }
        
        // Check whitelist
        bool is_safe = false;
        for (int i = 0; safe_tags[i]; i++) {
            if (strcmp(tag_name, safe_tags[i]) == 0) {
                is_safe = true;
                break;
            }
        }
        
        if (is_safe) {
            // Allow safe tag - copy original content but strip attributes
            size_t tag_content_len = strlen(tag_content);
            size_t remaining = max_output_size - output_pos;
            
            // Simple tag without attributes
            if (remaining >= tag_len + 2) {
                output[output_pos++] = '<';
                memcpy(output + output_pos, tag_start, tag_len);
                output_pos += tag_len;
                output[output_pos++] = '>';
            }
            return output_pos;
        }
    }
    
    // Unsafe tag - escape it
    size_t remaining = max_output_size - output_pos;
    if (remaining >= 4) {
        memcpy(output + output_pos, "&lt;", 4);
        return output_pos + 4;
    }
    
    return output_pos;
}