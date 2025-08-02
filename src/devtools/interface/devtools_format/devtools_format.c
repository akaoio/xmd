/**
 * @file devtools_format.c
 * @brief Format XMD code
 * 
 * This file contains ONLY the devtools_format function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../../include/devtools.h"
#include "../../../../include/utils.h"
/**
 * @brief Format XMD code
 * @param content Content to format
 * @return Formatted content (must be freed) or NULL on error
  * /
 */
char* devtools_format(const char* content) {
    if (!content) return NULL;
    
    // Simple formatting (in a real implementation, this would be much more sophisticated)
    size_t len = strlen(content);
    char* formatted = xmd_malloc(len * 2); // Allow for expansion
    if (!formatted) return NULL;
    
    size_t out_pos = 0;
    bool need_indent = true;
    int indent_level = 0;
    
    for (size_t i = 0; i < len; i++) {
        char c = content[i];
        
        if (need_indent && c != '\n' && c != '\r') {
            // Add indentation
            for (int j = 0; j < indent_level; j++) {
                formatted[out_pos++] = ' ';
                formatted[out_pos++] = ' ';
            }
            need_indent = false;
        }
        
        formatted[out_pos++] = c;
        
        if (c == '\n') {
            need_indent = true;
        } else if (c == '{') {
            indent_level++;
        } else if (c == '}') {
            indent_level = (indent_level > 0) ? indent_level - 1 : 0;
        }
    }
    
    formatted[out_pos] = '\0';
    return formatted;
}
