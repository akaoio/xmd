/**
 * @file security_sanitize_command_output.c
 * @brief Sanitize command output
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security sanitization subsystem
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"
/**
 * @brief Sanitize command output
 * @param output Command output to sanitize
 * @return Sanitized output (must be freed)
 */
char* security_sanitize_command_output(const char* output) {
    XMD_VALIDATE_PTRS(NULL, output);
    
    size_t len = strlen(output);
    char* sanitized;
    XMD_MALLOC_VALIDATED(sanitized, char, len * 2 + 1, NULL); // Extra space for escaping
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = output[i];
        
        // Escape potentially dangerous characters
        if (c == '<') {
            sanitized[j++] = '&';
            sanitized[j++] = 'l';
            sanitized[j++] = 't';
            sanitized[j++] = ';';
        } else if (c == '>') {
            sanitized[j++] = '&';
            sanitized[j++] = 'g';
            sanitized[j++] = 't';
            sanitized[j++] = ';';
        } else if (c == '&') {
            sanitized[j++] = '&';
            sanitized[j++] = 'a';
            sanitized[j++] = 'm';
            sanitized[j++] = 'p';
            sanitized[j++] = ';';
        } else {
            sanitized[j++] = c;
        }
    }
    sanitized[j] = '\0';
    return sanitized;
}
