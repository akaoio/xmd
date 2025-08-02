/**
 * @file extract_tag_name.c
 * @brief Extract tag name from HTML tag
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security utilities subsystem
 */

#include <stddef.h>
#include <ctype.h>
/**
 * @brief Extract tag name from HTML tag
 * @param tag_start Pointer to start of tag (after <)
 * @param tag_name Output buffer for tag name
 * @param max_len Maximum length of tag name
 * @return Length of tag name extracted
 */
size_t extract_tag_name(const char* tag_start, char* tag_name, size_t max_len) {
    size_t len = 0;
    const char* p = tag_start;
    
    // Skip leading whitespace
    while (*p && isspace(*p)) p++;
    
    // Skip closing tag indicator
    if (*p == '/') p++;
    
    // Extract tag name
    while (*p && !isspace(*p) && *p != '>' && *p != '/' && len < max_len - 1) {
        tag_name[len++] = tolower(*p++);
    }
    tag_name[len] = '\0';
    return len;
}
