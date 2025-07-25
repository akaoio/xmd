/**
 * @file sanitizer.c
 * @brief Output sanitization for safe rendering
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/security.h"

/**
 * @brief HTML-encode special characters
 * @param input Input string
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Length of encoded string or -1 on error
 */
static int html_encode(const char* input, char* output, size_t output_size) {
    if (!input || !output || output_size == 0) {
        return -1;
    }
    
    size_t input_len = strlen(input);
    size_t output_pos = 0;
    
    for (size_t i = 0; i < input_len && output_pos < output_size - 1; i++) {
        char c = input[i];
        const char* replacement = NULL;
        size_t replacement_len = 0;
        
        switch (c) {
            case '<':
                replacement = "&lt;";
                replacement_len = 4;
                break;
            case '>':
                replacement = "&gt;";
                replacement_len = 4;
                break;
            case '&':
                replacement = "&amp;";
                replacement_len = 5;
                break;
            case '"':
                replacement = "&quot;";
                replacement_len = 6;
                break;
            case '\'':
                replacement = "&#x27;";
                replacement_len = 6;
                break;
            case '/':
                replacement = "&#x2F;";
                replacement_len = 6;
                break;
            default:
                output[output_pos++] = c;
                continue;
        }
        
        if (output_pos + replacement_len >= output_size) {
            break;
        }
        
        memcpy(output + output_pos, replacement, replacement_len);
        output_pos += replacement_len;
    }
    
    output[output_pos] = '\0';
    return output_pos;
}

/**
 * @brief Remove dangerous HTML tags and attributes
 * @param input Input HTML string
 * @return Cleaned HTML string (must be freed) or NULL on error
 */
static char* remove_dangerous_html(const char* input) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    char* output = malloc(input_len + 1);
    if (!output) {
        return NULL;
    }
    
    // Dangerous tags to remove completely
    const char* dangerous_tags[] = {
        "script", "iframe", "object", "embed", "applet",
        "meta", "link", "style", "base", "form",
        "input", "button", "textarea", "select", "option",
        NULL
    };
    
    // Dangerous attributes to remove
    const char* dangerous_attrs[] = {
        "onload", "onerror", "onclick", "onmouseover", "onmouseout",
        "onkeydown", "onkeyup", "onkeypress", "onfocus", "onblur",
        "onchange", "onsubmit", "onreset", "onselect", "onunload",
        "javascript:", "vbscript:", "data:", "livescript:",
        NULL
    };
    
    size_t output_pos = 0;
    size_t i = 0;
    
    while (i < input_len) {
        if (input[i] == '<') {
            // Find the end of the tag
            size_t tag_start = i;
            size_t tag_end = i;
            
            while (tag_end < input_len && input[tag_end] != '>') {
                tag_end++;
            }
            
            if (tag_end < input_len) {
                tag_end++; // Include the '>'
                
                // Extract tag content
                size_t tag_content_len = tag_end - tag_start;
                char* tag_content = malloc(tag_content_len + 1);
                if (tag_content) {
                    memcpy(tag_content, input + tag_start, tag_content_len);
                    tag_content[tag_content_len] = '\0';
                    
                    // Convert to lowercase for comparison
                    char* lower_tag = malloc(tag_content_len + 1);
                    if (lower_tag) {
                        for (size_t j = 0; j <= tag_content_len; j++) {
                            lower_tag[j] = tolower(tag_content[j]);
                        }
                        
                        // Check if it's a dangerous tag
                        bool is_dangerous = false;
                        for (int t = 0; dangerous_tags[t]; t++) {
                            char tag_pattern[64];
                            snprintf(tag_pattern, sizeof(tag_pattern), "<%s", dangerous_tags[t]);
                            if (strstr(lower_tag, tag_pattern)) {
                                is_dangerous = true;
                                break;
                            }
                            snprintf(tag_pattern, sizeof(tag_pattern), "</%s", dangerous_tags[t]);
                            if (strstr(lower_tag, tag_pattern)) {
                                is_dangerous = true;
                                break;
                            }
                        }
                        
                        // Check for dangerous attributes
                        for (int a = 0; dangerous_attrs[a] && !is_dangerous; a++) {
                            if (strstr(lower_tag, dangerous_attrs[a])) {
                                is_dangerous = true;
                                break;
                            }
                        }
                        
                        if (!is_dangerous) {
                            // Copy the safe tag
                            memcpy(output + output_pos, tag_content, tag_content_len);
                            output_pos += tag_content_len;
                        }
                        
                        free(lower_tag);
                    }
                    free(tag_content);
                }
                
                i = tag_end;
            } else {
                // Malformed tag, copy as-is but encoded
                output[output_pos++] = input[i++];
            }
        } else {
            output[output_pos++] = input[i++];
        }
    }
    
    output[output_pos] = '\0';
    return output;
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
    
    size_t input_len = strlen(input);
    size_t output_size = input_len * 6 + 1; // Worst case for HTML encoding
    char* output = malloc(output_size);
    if (!output) {
        return NULL;
    }
    
    if (html_encode(input, output, output_size) < 0) {
        free(output);
        return NULL;
    }
    
    return output;
}

/**
 * @brief Sanitize HTML content
 * @param html HTML content to sanitize
 * @return Sanitized HTML (must be freed) or NULL on error
 */
char* security_sanitize_html(const char* html) {
    if (!html) {
        return NULL;
    }
    
    // First remove dangerous HTML elements
    char* cleaned = remove_dangerous_html(html);
    if (!cleaned) {
        return NULL;
    }
    
    // Return cleaned HTML (already safe)
    return cleaned;
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
    
    // First remove dangerous HTML elements
    char* html_cleaned = remove_dangerous_html(output);
    if (!html_cleaned) {
        return NULL;
    }
    
    size_t input_len = strlen(html_cleaned);
    size_t output_size = input_len * 2 + 1; // Space for escaping
    char* sanitized = malloc(output_size);
    if (!sanitized) {
        free(html_cleaned);
        return NULL;
    }
    
    size_t output_pos = 0;
    
    for (size_t i = 0; i < input_len && output_pos < output_size - 1; i++) {
        char c = html_cleaned[i];
        
        // Escape markdown special characters
        if (c == '*' || c == '_' || c == '`' || c == '#' || 
            c == '[' || c == ']' || c == '(' || c == ')' ||
            c == '\\' || c == '|') {
            if (output_pos < output_size - 2) {
                sanitized[output_pos++] = '\\';
                sanitized[output_pos++] = c;
            }
        }
        // Remove or escape control characters except newlines and tabs
        else if (iscntrl(c) && c != '\n' && c != '\t' && c != '\r') {
            // Skip control characters
            continue;
        }
        else {
            sanitized[output_pos++] = c;
        }
    }
    
    sanitized[output_pos] = '\0';
    free(html_cleaned);
    return sanitized;
}