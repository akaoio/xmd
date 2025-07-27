/**
 * @file security_sanitize_command_output.c
 * @brief Sanitize command output for inclusion in markdown
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/security.h"

/**
 * @brief Check if line contains potentially dangerous content
 * @param line Line to check
 * @return true if line is safe
 */
static bool is_safe_output_line(const char* line) {
    // Check for script injection in output
    if (strstr(line, "<script") || strstr(line, "</script>") ||
        strstr(line, "<iframe") || strstr(line, "<object") ||
        strstr(line, "<embed") || strstr(line, "javascript:") ||
        strstr(line, "vbscript:")) {
        return false;
    }
    
    // Check for potential XSS in markdown context
    if (strstr(line, "[javascript:") || strstr(line, "](javascript:") ||
        strstr(line, "[vbscript:") || strstr(line, "](vbscript:")) {
        return false;
    }
    
    // Check for potential command injection indicators
    if (strstr(line, "$(") || strstr(line, "`") ||
        strstr(line, "${IFS}") || strstr(line, "eval ")) {
        return false;
    }
    
    return true;
}

/**
 * @brief Escape special markdown characters
 * @param input Input string
 * @param output Output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Length of escaped string
 */
static size_t escape_markdown_chars(const char* input, char* output, size_t max_output_size) {
    const char* src = input;
    char* dst = output;
    char* end = output + max_output_size - 1;
    
    while (*src && dst < end - 1) {
        switch (*src) {
            case '*':
            case '_':
            case '`':
            case '[':
            case ']':
            case '(':
            case ')':
            case '#':
            case '!':
                if (dst + 1 < end) {
                    *dst++ = '\\';
                    *dst++ = *src;
                }
                break;
            case '<':
                if (dst + 4 <= end) {
                    strcpy(dst, "&lt;");
                    dst += 4;
                }
                break;
            case '>':
                if (dst + 4 <= end) {
                    strcpy(dst, "&gt;");
                    dst += 4;
                }
                break;
            case '&':
                if (dst + 5 <= end) {
                    strcpy(dst, "&amp;");
                    dst += 5;
                }
                break;
            default:
                // Only allow printable ASCII and some extended characters
                if ((*src >= 32 && *src < 127) || *src == '\n' || *src == '\r' || *src == '\t') {
                    *dst++ = *src;
                } else {
                    // Replace non-printable with placeholder
                    *dst++ = '?';
                }
                break;
        }
        src++;
    }
    
    *dst = '\0';
    return dst - output;
}

/**
 * @brief Remove ANSI escape codes from output
 * @param input Input string with potential ANSI codes
 * @param output Output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Length of cleaned string
 */
static size_t remove_ansi_codes(const char* input, char* output, size_t max_output_size) {
    const char* src = input;
    char* dst = output;
    char* end = output + max_output_size - 1;
    
    while (*src && dst < end) {
        if (*src == '\033' || *src == '\x1b') {
            // Start of ANSI escape sequence
            src++; // Skip ESC
            if (*src == '[') {
                src++; // Skip [
                // Skip until we find the end character (usually m, but could be others)
                while (*src && *src != 'm' && *src != 'K' && *src != 'J' && 
                       *src != 'H' && *src != 'f' && dst < end) {
                    src++;
                }
                if (*src) src++; // Skip the end character
            }
        } else {
            *dst++ = *src++;
        }
    }
    
    *dst = '\0';
    return dst - output;
}

/**
 * @brief Limit output length and add truncation message if needed
 * @param input Input string
 * @param max_length Maximum allowed length
 * @return Potentially truncated string (must be freed) or NULL on error
 */
static char* limit_output_length(const char* input, size_t max_length) {
    size_t input_len = strlen(input);
    
    if (input_len <= max_length) {
        return strdup(input);
    }
    
    // Truncate and add message
    const char* truncation_msg = "\n\n[Output truncated due to length limit]";
    size_t msg_len = strlen(truncation_msg);
    size_t truncate_at = max_length - msg_len;
    
    char* result = malloc(max_length + 1);
    if (!result) return NULL;
    
    memcpy(result, input, truncate_at);
    strcpy(result + truncate_at, truncation_msg);
    
    return result;
}

/**
 * @brief Sanitize command output for inclusion in markdown
 * @param output Command output to sanitize
 * @return Sanitized output (must be freed) or NULL on error
 */
char* security_sanitize_command_output(const char* output) {
    if (!output) {
        return NULL;
    }
    
    size_t input_len = strlen(output);
    if (input_len == 0) {
        return strdup("");
    }
    
    // Allocate buffer for intermediate processing
    char* temp_buffer = malloc(input_len * 3 + 1); // Extra space for escaping
    if (!temp_buffer) {
        return NULL;
    }
    
    // Remove ANSI escape codes first
    size_t clean_len = remove_ansi_codes(output, temp_buffer, input_len * 3);
    
    // Check each line for safety
    char* line_start = temp_buffer;
    char* line_end;
    bool has_unsafe_content = false;
    
    while ((line_end = strchr(line_start, '\n')) != NULL) {
        *line_end = '\0'; // Temporarily null-terminate line
        
        if (!is_safe_output_line(line_start)) {
            has_unsafe_content = true;
            break;
        }
        
        *line_end = '\n'; // Restore newline
        line_start = line_end + 1;
    }
    
    // Check last line if no newline at end
    if (!has_unsafe_content && *line_start) {
        has_unsafe_content = !is_safe_output_line(line_start);
    }
    
    if (has_unsafe_content) {
        free(temp_buffer);
        return strdup("[Command output contained potentially unsafe content and was filtered]");
    }
    
    // Escape markdown characters
    char* escaped_buffer = malloc(input_len * 4 + 1); // More space for escaping
    if (!escaped_buffer) {
        free(temp_buffer);
        return NULL;
    }
    
    escape_markdown_chars(temp_buffer, escaped_buffer, input_len * 4);
    free(temp_buffer);
    
    // Limit output length (e.g., 10KB max)
    char* result = limit_output_length(escaped_buffer, 10240);
    free(escaped_buffer);
    
    return result;
}