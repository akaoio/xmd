/**
 * @file validator.c
 * @brief Input validation for security threats
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/security.h"

/**
 * @brief Check for null bytes in input
 * @param input Input string to check
 * @param length Length of input
 * @return Security validation result
 */
security_result security_check_null_bytes(const char* input, size_t length) {
    if (!input) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for embedded null bytes which could indicate binary data
    for (size_t i = 0; i < length; i++) {
        if (input[i] == '\0' && i < length - 1) {
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    return SECURITY_VALID;
}
