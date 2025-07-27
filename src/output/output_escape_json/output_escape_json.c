/**
 * @file output_escape_json.c
 * @brief JSON escaping function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Escape JSON special characters
 * @param input Input text
 * @param result Escaped output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_escape_json(const char* input, char** result) {
    if (!input || !result) {
        return OUTPUT_ERROR;
    }
    
    size_t input_len = strlen(input);
    size_t output_size = input_len * 6 + 1; // Worst case: every char becomes \uxxxx
    char* output = malloc(output_size);
    if (!output) {
        return OUTPUT_ERROR;
    }
    
    char* out_ptr = output;
    for (const char* in_ptr = input; *in_ptr; in_ptr++) {
        switch (*in_ptr) {
            case '"':
                strcpy(out_ptr, "\\\"");
                out_ptr += 2;
                break;
            case '\\':
                strcpy(out_ptr, "\\\\");
                out_ptr += 2;
                break;
            case '/':
                strcpy(out_ptr, "\\/");
                out_ptr += 2;
                break;
            case '\b':
                strcpy(out_ptr, "\\b");
                out_ptr += 2;
                break;
            case '\f':
                strcpy(out_ptr, "\\f");
                out_ptr += 2;
                break;
            case '\n':
                strcpy(out_ptr, "\\n");
                out_ptr += 2;
                break;
            case '\r':
                strcpy(out_ptr, "\\r");
                out_ptr += 2;
                break;
            case '\t':
                strcpy(out_ptr, "\\t");
                out_ptr += 2;
                break;
            default:
                if (*in_ptr < 32) {
                    sprintf(out_ptr, "\\u%04x", (unsigned char)*in_ptr);
                    out_ptr += 6;
                } else {
                    *out_ptr++ = *in_ptr;
                }
                break;
        }
    }
    *out_ptr = '\0';
    
    *result = output;
    return OUTPUT_SUCCESS;
}