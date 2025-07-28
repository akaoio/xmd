/**
 * @file process_escape_sequences.c
 * @brief Process escape sequences in string literals
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>

/**
 * @brief Process escape sequences in a string literal
 * @param input Input string with potential escape sequences
 * @return New string with processed escape sequences (caller must free) or NULL on error
 */
char* process_escape_sequences(const char* input) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    char* output = malloc(input_len + 1); // Max possible length
    if (!output) {
        return NULL;
    }
    
    size_t out_pos = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] == '\\' && i + 1 < input_len) {
            // Process escape sequence
            switch (input[i + 1]) {
                case 'n':
                    output[out_pos++] = '\n';
                    i++; // Skip the next character
                    break;
                case 't':
                    output[out_pos++] = '\t';
                    i++; // Skip the next character
                    break;
                case 'r':
                    output[out_pos++] = '\r';
                    i++; // Skip the next character
                    break;
                case '\\':
                    output[out_pos++] = '\\';
                    i++; // Skip the next character
                    break;
                case '"':
                    output[out_pos++] = '"';
                    i++; // Skip the next character
                    break;
                case '\'':
                    output[out_pos++] = '\'';
                    i++; // Skip the next character
                    break;
                default:
                    // Unknown escape sequence, keep as-is
                    output[out_pos++] = input[i];
                    break;
            }
        } else {
            output[out_pos++] = input[i];
        }
    }
    
    output[out_pos] = '\0';
    return output;
}