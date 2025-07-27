/**
 * @file output_format_as_code.c
 * @brief Code block formatting function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Format text as code block
 * @param input Input text
 * @param language Programming language (can be NULL)
 * @param result Formatted output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_format_as_code(const char* input, const char* language, char** result) {
    if (!input || !result) {
        return OUTPUT_ERROR;
    }
    
    size_t input_len = strlen(input);
    size_t lang_len = language ? strlen(language) : 0;
    size_t output_size = input_len + lang_len + 20; // Extra space for markdown
    
    char* output = malloc(output_size);
    if (!output) {
        return OUTPUT_ERROR;
    }
    
    if (language) {
        snprintf(output, output_size, "```%s\n%s\n```", language, input);
    } else {
        snprintf(output, output_size, "```\n%s\n```", input);
    }
    
    *result = output;
    return OUTPUT_SUCCESS;
}