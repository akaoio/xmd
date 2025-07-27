#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file output_truncate.c
 * @brief Text truncation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Truncate text to maximum length
 * @param input Input text
 * @param max_length Maximum length (excluding ellipsis)
 * @param result Truncated output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_truncate(const char* input, size_t max_length, char** result) {
    if (!input || !result) {
        return OUTPUT_ERROR;
    }
    
    size_t input_len = strlen(input);
    if (input_len <= max_length) {
        *result = strdup(input);
        return *result ? OUTPUT_SUCCESS : OUTPUT_ERROR;
    }
    
    char* output = malloc(max_length + 4); // +3 for "..." +1 for null
    if (!output) {
        return OUTPUT_ERROR;
    }
    
    strncpy(output, input, max_length);
    strcpy(output + max_length, "...");
    
    *result = output;
    return OUTPUT_SUCCESS;
}