/**
 * @file output_strip_ansi_codes.c
 * @brief ANSI code stripping function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/output.h"

/**
 * @brief Strip ANSI color codes from text
 * @param input Input text with ANSI codes
 * @param result Cleaned output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_strip_ansi_codes(const char* input, char** result) {
    if (!input || !result) {
        return OUTPUT_ERROR;
    }
    
    size_t input_len = strlen(input);
    char* output = malloc(input_len + 1);
    if (!output) {
        return OUTPUT_ERROR;
    }
    
    char* out_ptr = output;
    const char* in_ptr = input;
    
    while (*in_ptr) {
        if (*in_ptr == '\033' && *(in_ptr + 1) == '[') {
            // Skip ANSI escape sequence
            in_ptr += 2;
            while (*in_ptr && !isalpha(*in_ptr)) {
                in_ptr++;
            }
            if (*in_ptr) {
                in_ptr++; // Skip the final character
            }
        } else {
            *out_ptr++ = *in_ptr++;
        }
    }
    
    *out_ptr = '\0';
    *result = output;
    return OUTPUT_SUCCESS;
}