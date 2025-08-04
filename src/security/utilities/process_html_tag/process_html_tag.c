/**
 * @file process_html_tag.c
 * @brief Process HTML tag and determine if it should be kept
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security utilities subsystem
 */

#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../../../utils/common/common_macros.h"

// Forward declarations
bool is_safe_html_tag(const char* tag);
size_t extract_tag_name(const char* tag_start, char* tag_name, size_t max_len);
/**
 * @brief Process HTML tag and determine if it should be kept
 * @param tag_content Full tag content including brackets
 * @param output Output buffer
 * @param output_pos Current position in output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Updated output position
 */
size_t process_html_tag(const char* tag_content, char* output, 
                              size_t output_pos, size_t max_output_size) {
    if (!tag_content || !output) return output_pos;
    if (tag_content[0] != '<') return output_pos;
    
    char tag_name[32];
    size_t tag_len = extract_tag_name(tag_content + 1, tag_name, sizeof(tag_name));
    if (tag_len == 0) return output_pos;
    
    // Check if tag is safe
    if (!is_safe_html_tag(tag_name)) {
        return output_pos; // Skip dangerous tag
    }
    
    // Find end of tag
    const char* tag_end = strchr(tag_content, '>');
    if (!tag_end) return output_pos;
    
    size_t tag_full_len = tag_end - tag_content + 1;
    
    // For safe tags, copy them (could add attribute filtering here)
    if (output_pos + tag_full_len < max_output_size) {
        memcpy(output + output_pos, tag_content, tag_full_len);
        output_pos += tag_full_len;
    }
    
    return output_pos;
}
