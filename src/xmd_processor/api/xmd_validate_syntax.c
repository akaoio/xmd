/**
 * @file xmd_validate_syntax.c
 * @brief Validate XMD syntax implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Validate XMD syntax
 * @param input Input content to validate
 * @param input_length Length of input content
 * @return XMD_SUCCESS if valid, error code otherwise
 */
xmd_error_code xmd_validate_syntax(const char* input, size_t input_length) {
    // Basic syntax validation
    if (!input || input_length == 0) {
        return XMD_ERROR_INVALID_ARGUMENT;
    }
    
    // Check for balanced XMD comment tags
    const char* ptr = input;
    int comment_depth = 0;
    
    while (ptr < input + input_length) {
        if (strncmp(ptr, "<!--", 4) == 0) {
            if (strncmp(ptr + 4, " xmd:", 5) == 0 || strncmp(ptr + 4, "xmd:", 4) == 0) {
                comment_depth++;
            }
            ptr += 4;
        } else if (strncmp(ptr, "-->", 3) == 0) {
            if (comment_depth > 0) {
                comment_depth--;
            }
            ptr += 3;
        } else {
            ptr++;
        }
    }
    
    return (comment_depth == 0) ? XMD_SUCCESS : XMD_ERROR_SYNTAX;
}
