/**
 * @file output_escape_html.c
 * @brief HTML escaping function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Escape HTML special characters
 * @param input Input text
 * @param result Escaped output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_escape_html(const char* input, char** result) {
    if (!input || !result) {
        return OUTPUT_ERROR;
    }
    
    size_t input_len = strlen(input);
    size_t output_size = input_len * 6 + 1; // Worst case: every char becomes &xxxx;
    char* output = malloc(output_size);
    if (!output) {
        return OUTPUT_ERROR;
    }
    
    char* out_ptr = output;
    for (const char* in_ptr = input; *in_ptr; in_ptr++) {
        switch (*in_ptr) {
            case '<':
                strcpy(out_ptr, "&lt;");
                out_ptr += 4;
                break;
            case '>':
                strcpy(out_ptr, "&gt;");
                out_ptr += 4;
                break;
            case '&':
                strcpy(out_ptr, "&amp;");
                out_ptr += 5;
                break;
            case '"':
                strcpy(out_ptr, "&quot;");
                out_ptr += 6;
                break;
            case '\'':
                strcpy(out_ptr, "&#39;");
                out_ptr += 5;
                break;
            default:
                *out_ptr++ = *in_ptr;
                break;
        }
    }
    *out_ptr = '\0';
    
    *result = output;
    return OUTPUT_SUCCESS;
}