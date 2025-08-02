/**
 * @file xmd_strtrim.c
 * @brief Trim whitespace from string
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include "../../../../include/utils.h"
/**
 * @brief Trim whitespace from string
 * @param str String to trim (modified in place)
 * @return Trimmed string
 */
char* xmd_strtrim(char* str) {
    if (!str) {
        return NULL;
    }
    
    // Trim leading whitespace
    char* start = str;
    while (*start && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) {
        start++;
    }
    
    // Trim trailing whitespace
    char* end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
    
    // Move trimmed string to beginning if needed
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
    
    return str;
}
