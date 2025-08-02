/**
 * @file xmd_validate.c
 * @brief Validate XMD content syntax
 * 
 * This file contains ONLY the xmd_validate function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../../include/xmd.h"
#include "utils/common/common_macros.h"
#include <string.h>

/**
 * @brief Validate XMD content syntax
 * @param content XMD content to validate
 * @return XMD_SUCCESS if valid, XMD_ERROR if invalid
 */
xmd_error_code xmd_validate(const char* content) {
    XMD_VALIDATE_PTRS(XMD_ERROR, content);
    
    // Empty content is valid
    if (strlen(content) == 0) {
        return XMD_SUCCESS;
    }
    
    // Basic syntax validation
    size_t len = strlen(content);
    bool in_directive = false;
    bool in_string = false;
    int brace_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        char c = content[i];
        
        // Handle string literals
        if (c == '"' && (i == 0 || content[i-1] != '\\')) {
            in_string = !in_string;
            continue;
        }
        
        // Skip validation inside strings
        if (in_string) {
            continue;
        }
        
        // Check for directive markers
        if (c == '{' && i + 1 < len && content[i + 1] == '{') {
            in_directive = true;
            brace_count++;
            i++; // Skip next brace
            continue;
        }
        
        if (c == '}' && i + 1 < len && content[i + 1] == '}') {
            if (!in_directive || brace_count == 0) {
                // Unmatched closing braces
                return XMD_ERROR;
            }
            brace_count--;
            if (brace_count == 0) {
                in_directive = false;
            }
            i++; // Skip next brace
            continue;
        }
    }
    
    // Check for unmatched braces
    if (brace_count != 0 || in_directive) {
        return XMD_ERROR;
    }
    
    return XMD_SUCCESS;
}