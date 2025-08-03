/**
 * @file xmd_is_native_syntax.c
 * @brief Check if content uses Genesis's native XMD syntax
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/native_xmd.h"
#include "../../../include/utils.h"

/**
 * @brief Check if content uses Genesis's native XMD syntax
 * @param content Input content to analyze
 * @return true if native XMD syntax detected
 */
bool xmd_is_native_syntax(const char* content) {
    if (!content) {
        return false;
    }
    
    // Look for native XMD keywords at start of lines
    const char* pos = content;
    while (*pos) {
        // Skip whitespace at start of line
        while (*pos && (*pos == ' ' || *pos == '\t')) {
            pos++;
        }
        
        // Check for native XMD keywords
        if (strncmp(pos, "set ", 4) == 0 ||
            strncmp(pos, "if ", 3) == 0 ||
            strncmp(pos, "for ", 4) == 0 ||
            strncmp(pos, "while ", 6) == 0 ||
            strncmp(pos, "function ", 9) == 0 ||
            strncmp(pos, "class ", 6) == 0 ||
            strncmp(pos, "print ", 6) == 0 ||
            strstr(pos, "${") != NULL) {  // Native variable syntax
            return true;
        }
        
        // Move to next line
        while (*pos && *pos != '\n') {
            pos++;
        }
        if (*pos == '\n') {
            pos++;
        }
    }
    
    return false;
}
