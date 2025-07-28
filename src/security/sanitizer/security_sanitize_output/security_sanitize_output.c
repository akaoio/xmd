/**
 * @file security_sanitize_output.c
 * @brief Sanitize output string for safe rendering
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/security.h"

/**
 * @brief Calculate required buffer size for escaped output
 * @param input Input string
 * @return Required buffer size
 */
static size_t calculate_escaped_size(const char* input) {
    size_t size = 1; // for null terminator
    
    for (const char* p = input; *p; p++) {
        switch (*p) {
            case '<':
            case '>':
                size += 4; // &lt; or &gt;
                break;
            case '&':
                size += 5; // &amp;
                break;
            case '"':
                size += 6; // &quot;
                break;
            case '\'':
                size += 6; // &#x27;
                break;
            default:
                size += 1;
                break;
        }
    }
    
    return size;
}

/**
 * @brief Escape HTML entities in string
 * @param input Input string
 * @param output Output buffer
 * @param output_size Size of output buffer
 */
static void escape_html_entities(const char* input, char* output, size_t output_size) {
    const char* src = input;
    char* dst = output;
    char* end = output + output_size - 1;
    
    while (*src && dst < end - 10) { // Leave room for longest escape sequence
        switch (*src) {
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
            case '"':
                if (dst + 6 <= end) {
                    strcpy(dst, "&quot;");
                    dst += 6;
                }
                break;
            case '\'':
                if (dst + 6 <= end) {
                    strcpy(dst, "&#x27;");
                    dst += 6;
                }
                break;
            default:
                // Only allow printable ASCII characters
                if (*src >= 32 && *src < 127) {
                    *dst++ = *src;
                } else {
                    // Replace non-printable with space
                    *dst++ = ' ';
                }
                break;
        }
        src++;
    }
    
    *dst = '\0';
}

/**
 * @brief Remove dangerous script tags and content
 * @param input Input string
 * @return Cleaned string (must be freed) or NULL on error
 */
static char* remove_script_content(const char* input) {
    if (!input) return NULL;
    
    size_t len = strlen(input);
    char* result = malloc(len + 1);
    if (!result) return NULL;
    
    const char* src = input;
    char* dst = result;
    
    while (*src) {
        // Look for script tag start
        if (strncasecmp(src, "<script", 7) == 0) {
            // Skip until we find closing script tag
            const char* script_end = strcasestr(src, "</script>");
            if (script_end) {
                src = script_end + 9;
                continue;
            } else {
                // No closing tag found, skip rest
                break;
            }
        }
        
        // Look for other dangerous tags
        if (strncasecmp(src, "<iframe", 7) == 0 ||
            strncasecmp(src, "<object", 7) == 0 ||
            strncasecmp(src, "<embed", 6) == 0) {
            
            // Find end of tag
            const char* tag_end = strchr(src, '>');
            if (tag_end) {
                src = tag_end + 1;
                continue;
            }
        }
        
        // Look for javascript: or vbscript: URLs
        if (strncasecmp(src, "javascript:", 11) == 0 ||
            strncasecmp(src, "vbscript:", 9) == 0) {
            // Skip the dangerous URL
            while (*src && *src != ' ' && *src != '"' && *src != '\'' && *src != '>') {
                src++;
            }
            continue;
        }
        
        *dst++ = *src++;
    }
    
    *dst = '\0';
    return result;
}

/**
 * @brief Sanitize output string for safe rendering
 * @param input Input string to sanitize
 * @return Sanitized string (must be freed) or NULL on error
 */
char* security_sanitize_output(const char* input) {
    if (!input) {
        return NULL;
    }
    
    // First remove dangerous script content
    char* cleaned = remove_script_content(input);
    if (!cleaned) {
        return NULL;
    }
    
    // Calculate buffer size needed for HTML escaping
    size_t escaped_size = calculate_escaped_size(cleaned);
    char* result = malloc(escaped_size);
    if (!result) {
        free(cleaned);
        return NULL;
    }
    
    // Escape HTML entities
    escape_html_entities(cleaned, result, escaped_size);
    
    free(cleaned);
    return result;
}