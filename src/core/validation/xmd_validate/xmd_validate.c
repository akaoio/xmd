/**
 * @file xmd_validate.c
 * @brief XMD content validation function - Genesis compliant
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../../include/xmd.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Validate XMD content syntax
 * @param content XMD content to validate
 * @return true if valid, false if invalid
 */
bool xmd_validate(const char* content) {
    if (!content) {
        return false;
    }
    
    // Basic XMD syntax validation
    size_t len = strlen(content);
    int brace_count = 0;
    int bracket_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        char c = content[i];
        
        switch (c) {
            case '{':
                brace_count++;
                break;
            case '}':
                brace_count--;
                if (brace_count < 0) {
                    return false; // Unmatched closing brace
                }
                break;
            case '[':
                bracket_count++;
                break;
            case ']':
                bracket_count--;
                if (bracket_count < 0) {
                    return false; // Unmatched closing bracket
                }
                break;
        }
    }
    
    // Check for balanced braces and brackets
    return (brace_count == 0 && bracket_count == 0);
}
