/**
 * @file is_multiline_directive.c
 * @brief Check if comment contains multiline directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Check if comment contains multiline directive
 * @param comment_content Content of the HTML comment
 * @return true if multiline directive, false otherwise
 */
bool is_multiline_directive(const char* comment_content) {
    const char* xmd_pos = strstr(comment_content, "xmd:");
    if (!xmd_pos) return false;
    
    const char* after_xmd = xmd_pos + 4;
    while (*after_xmd && (*after_xmd == ' ' || *after_xmd == '\t')) after_xmd++;
    
    return (*after_xmd == '\n' || *after_xmd == '\r');
}
