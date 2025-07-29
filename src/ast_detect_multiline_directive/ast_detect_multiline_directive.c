/**
 * @file ast_detect_multiline_directive.c
 * @brief Detect if a directive is multiline
 * @author XMD Team
 * @date 2025-07-29
 */

#include <string.h>
#include <stdbool.h>

/**
 * @brief Check if directive content contains multiple lines
 * @param content Directive content
 * @return true if multiline, false otherwise
 */
bool ast_detect_multiline_directive(const char* content) {
    if (!content) return false;
    
    // Skip initial whitespace and newlines
    while (*content == ' ' || *content == '\t' || *content == '\n') content++;
    
    // Check for newline in the remaining content
    const char* newline = strchr(content, '\n');
    if (!newline) return false;
    
    // Check if there's non-whitespace content after the newline
    newline++;
    while (*newline) {
        if (*newline != ' ' && *newline != '\t' && *newline != '\n') {
            return true;  // Found non-whitespace content on another line
        }
        newline++;
    }
    
    return false;
}