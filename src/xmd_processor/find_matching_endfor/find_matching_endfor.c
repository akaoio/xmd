/**
 * @file find_matching_endfor.c
 * @brief Find matching endfor directive function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Find matching endfor for a for directive
 * @param start Starting position to search from
 * @param input_end End of input buffer
 * @return Pointer to position after matching endfor, or NULL if not found
 */
const char* find_matching_endfor(const char* start, const char* input_end) {
    const char* ptr = start;
    int for_count = 1;
    
    while (ptr < input_end && for_count > 0) {
        const char* comment_start = strstr(ptr, "<!--");
        if (!comment_start) break;
        
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) break;
        
        // Extract comment content
        size_t comment_len = comment_end - comment_start - 4;
        char* comment_content = malloc(comment_len + 1);
        strncpy(comment_content, comment_start + 4, comment_len);
        comment_content[comment_len] = '\0';
        
        char* trimmed = trim_whitespace(comment_content);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            char* directive = trim_whitespace(trimmed + 4);
            if (strncmp(directive, "for ", 4) == 0) {
                for_count++;
            } else if (strcmp(directive, "endfor") == 0) {
                for_count--;
                if (for_count == 0) {
                    free(comment_content);
                    return comment_end + 3;
                }
            }
        }
        
        free(comment_content);
        ptr = comment_end + 3;
    }
    
    return NULL;
}