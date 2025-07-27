/**
 * @file sanitizer.c
 * @brief Output sanitization for safe rendering
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/security.h"

/**
 * @brief Sanitize output string for safe rendering
 * @param input Input string to sanitize
 * @return Sanitized string (must be freed) or NULL on error
 */
char* security_sanitize_output(const char* input) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    size_t output_size = input_len * 6 + 1; // Worst case for HTML encoding
    char* output = malloc(output_size);
    if (!output) {
        return NULL;
    }
    
    size_t output_pos = 0;
    
    for (size_t i = 0; i < input_len && output_pos < output_size - 1; i++) {
        char c = input[i];
        const char* replacement = NULL;
        size_t replacement_len = 0;
        
        switch (c) {
            case '<':
                replacement = "&lt;";
                replacement_len = 4;
                break;
            case '>':
                replacement = "&gt;";
                replacement_len = 4;
                break;
            case '&':
                replacement = "&amp;";
                replacement_len = 5;
                break;
            case '"':
                replacement = "&quot;";
                replacement_len = 6;
                break;
            case '\'':
                replacement = "&#x27;";
                replacement_len = 6;
                break;
            case '/':
                replacement = "&#x2F;";
                replacement_len = 6;
                break;
            default:
                output[output_pos++] = c;
                continue;
        }
        
        if (output_pos + replacement_len >= output_size) {
            break;
        }
        
        memcpy(output + output_pos, replacement, replacement_len);
        output_pos += replacement_len;
    }
    
    output[output_pos] = '\0';
    return output;
}
