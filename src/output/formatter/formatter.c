/**
 * @file formatter.c
 * @brief Output formatting implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/output.h"

/**
 * @brief Output formatter context structure
 */
struct output_formatter {
    char* last_error;           /**< Last error message */
};

/**
 * @brief Create a new output formatter
 * @return New output formatter or NULL on error
 */
OutputFormatter* output_formatter_new(void) {
    OutputFormatter* formatter = malloc(sizeof(OutputFormatter));
    if (!formatter) {
        return NULL;
    }
    
    formatter->last_error = NULL;
    
    return formatter;
}

/**
 * @brief Free an output formatter
 * @param formatter Formatter to free
 */
void output_formatter_free(OutputFormatter* formatter) {
    if (!formatter) {
        return;
    }
    
    free(formatter->last_error);
    free(formatter);
}

/**
 * @brief Set error message in formatter
 * @param formatter Output formatter
 * @param message Error message
 */
static void set_formatter_error(OutputFormatter* formatter, const char* message) {
    if (!formatter || !message) {
        return;
    }
    
    free(formatter->last_error);
    formatter->last_error = strdup(message);
}

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
