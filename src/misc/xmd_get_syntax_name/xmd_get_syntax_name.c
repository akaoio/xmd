/**
 * @file xmd_get_syntax_name.c
 * @brief Get syntax type name for debugging
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/native_xmd.h"
#include "../../../include/utils.h"

// Forward declaration for dependency
extern bool xmd_is_native_syntax(const char* content);

/**
 * @brief Get syntax type name for debugging
 * @param content Input content to analyze  
 * @return Human-readable syntax type name
 */
const char* xmd_get_syntax_name(const char* content) {
    if (!content) {
        return "empty";
    }
    
    if (xmd_is_native_syntax(content)) {
        return "native-xmd";
    }
    
    // Check for HTML comments (legacy XMD syntax)
    if (strstr(content, "<!--") != NULL) {
        return "html-comment-xmd";
    }
    
    return "plain-text";
}