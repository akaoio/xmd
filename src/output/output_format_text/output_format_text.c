#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file output_format_text.c
 * @brief Text formatting function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Format text according to specified format
 * @param formatter Output formatter
 * @param input Input text to format
 * @param format Output format
 * @param result Formatted output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_format_text(OutputFormatter* formatter, const char* input, 
                      OutputFormat format, char** result) {
    if (!formatter || !input || !result) {
        return OUTPUT_ERROR;
    }
    
    switch (format) {
        case OUTPUT_FORMAT_RAW:
            *result = strdup(input);
            return *result ? OUTPUT_SUCCESS : OUTPUT_ERROR;
            
        case OUTPUT_FORMAT_CODE:
            return output_format_as_code(input, NULL, result);
            
        case OUTPUT_FORMAT_MARKDOWN:
            // For markdown, just ensure it's escaped properly
            *result = strdup(input);
            return *result ? OUTPUT_SUCCESS : OUTPUT_ERROR;
            
        case OUTPUT_FORMAT_HTML:
            return output_escape_html(input, result);
            
        case OUTPUT_FORMAT_JSON:
            return output_escape_json(input, result);
            
        default:
            set_formatter_error(formatter, "Invalid output format");
            return OUTPUT_INVALID_FORMAT;
    }
}