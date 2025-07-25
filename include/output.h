/**
 * @file output.h
 * @brief Output formatting system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Output formatter context
 */
typedef struct output_formatter OutputFormatter;

/**
 * @brief Output format types
 */
typedef enum {
    OUTPUT_FORMAT_RAW,          /**< Raw output, no formatting */
    OUTPUT_FORMAT_CODE,         /**< Format as code block */
    OUTPUT_FORMAT_MARKDOWN,     /**< Format as markdown */
    OUTPUT_FORMAT_HTML,         /**< Format as HTML (escaped) */
    OUTPUT_FORMAT_JSON          /**< Format as JSON (escaped) */
} OutputFormat;

/**
 * @brief Output result codes
 */
typedef enum {
    OUTPUT_SUCCESS = 0,         /**< Operation successful */
    OUTPUT_ERROR = -1,          /**< General error */
    OUTPUT_INVALID_FORMAT = -2  /**< Invalid format specified */
} OutputResult;

/**
 * @brief Create a new output formatter
 * @return New output formatter or NULL on error
 */
OutputFormatter* output_formatter_new(void);

/**
 * @brief Free an output formatter
 * @param formatter Formatter to free
 */
void output_formatter_free(OutputFormatter* formatter);

/**
 * @brief Format text according to specified format
 * @param formatter Output formatter
 * @param input Input text to format
 * @param format Output format
 * @param result Formatted output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_format_text(OutputFormatter* formatter, const char* input, 
                      OutputFormat format, char** result);

/**
 * @brief Escape HTML special characters
 * @param input Input text
 * @param result Escaped output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_escape_html(const char* input, char** result);

/**
 * @brief Escape JSON special characters
 * @param input Input text
 * @param result Escaped output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_escape_json(const char* input, char** result);

/**
 * @brief Format text as code block
 * @param input Input text
 * @param language Programming language (can be NULL)
 * @param result Formatted output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_format_as_code(const char* input, const char* language, char** result);

/**
 * @brief Strip ANSI color codes from text
 * @param input Input text with ANSI codes
 * @param result Cleaned output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_strip_ansi_codes(const char* input, char** result);

/**
 * @brief Truncate text to maximum length
 * @param input Input text
 * @param max_length Maximum length (excluding ellipsis)
 * @param result Truncated output (caller must free)
 * @return OutputResult indicating success/failure
 */
int output_truncate(const char* input, size_t max_length, char** result);

#ifdef __cplusplus
}
#endif

#endif /* OUTPUT_H */