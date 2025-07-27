/**
 * @file security_sanitize_html.c
 * @brief Sanitize HTML content
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/security.h"

/**
 * @brief Check if tag is in whitelist of safe HTML tags
 * @param tag Tag name to check
 * @return true if tag is safe
 */
static bool is_safe_html_tag(const char* tag) {
    static const char* safe_tags[] = {
        "p", "br", "strong", "b", "em", "i", "u", "h1", "h2", "h3", "h4", "h5", "h6",
        "ul", "ol", "li", "blockquote", "pre", "code", "span", "div", "a", "img",
        "table", "tr", "td", "th", "tbody", "thead", "tfoot",
        NULL
    };
    
    for (int i = 0; safe_tags[i] != NULL; i++) {
        if (strcasecmp(tag, safe_tags[i]) == 0) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Check if attribute is safe for HTML tags
 * @param attr Attribute name to check
 * @return true if attribute is safe
 */
static bool is_safe_html_attribute(const char* attr) {
    static const char* safe_attrs[] = {
        "id", "class", "href", "src", "alt", "title", "width", "height",
        "colspan", "rowspan", "align", "valign",
        NULL
    };
    
    for (int i = 0; safe_attrs[i] != NULL; i++) {
        if (strcasecmp(attr, safe_attrs[i]) == 0) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Extract tag name from HTML tag
 * @param tag_start Pointer to start of tag (after <)
 * @param tag_name Output buffer for tag name
 * @param max_len Maximum length of tag name
 * @return Length of tag name extracted
 */
static size_t extract_tag_name(const char* tag_start, char* tag_name, size_t max_len) {
    size_t len = 0;
    const char* p = tag_start;
    
    // Skip leading whitespace
    while (*p && isspace(*p)) p++;
    
    // Skip closing tag indicator
    if (*p == '/') p++;
    
    // Extract tag name
    while (*p && !isspace(*p) && *p != '>' && *p != '/' && len < max_len - 1) {
        tag_name[len++] = tolower(*p++);
    }
    
    tag_name[len] = '\0';
    return len;
}

/**
 * @brief Check if attribute value is safe
 * @param attr_name Attribute name
 * @param attr_value Attribute value
 * @return true if attribute value is safe
 */
static bool is_safe_attribute_value(const char* attr_name, const char* attr_value) {
    if (!attr_value) return false;
    
    // Check for javascript: or vbscript: URLs
    if (strcasecmp(attr_name, "href") == 0 || strcasecmp(attr_name, "src") == 0) {
        if (strncasecmp(attr_value, "javascript:", 11) == 0 ||
            strncasecmp(attr_value, "vbscript:", 9) == 0 ||
            strncasecmp(attr_value, "data:", 5) == 0) {
            return false;
        }
    }
    
    // Check for event handlers
    if (strncasecmp(attr_name, "on", 2) == 0) {
        return false;
    }
    
    // Check for dangerous content in any attribute
    if (strstr(attr_value, "<script") || strstr(attr_value, "javascript:") ||
        strstr(attr_value, "vbscript:") || strstr(attr_value, "expression(")) {
        return false;
    }
    
    return true;
}

/**
 * @brief Process HTML tag and determine if it should be kept
 * @param tag_content Full tag content including brackets
 * @param output Output buffer
 * @param output_pos Current position in output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Updated output position
 */
static size_t process_html_tag(const char* tag_content, char* output, 
                              size_t output_pos, size_t max_output_size) {
    if (tag_content[0] != '<') return output_pos;
    
    // Extract tag name
    char tag_name[32];
    size_t tag_len = extract_tag_name(tag_content + 1, tag_name, sizeof(tag_name));
    
    if (tag_len == 0) return output_pos;
    
    // Check if tag is safe
    if (!is_safe_html_tag(tag_name)) {
        return output_pos; // Skip dangerous tag
    }
    
    // Find end of tag
    const char* tag_end = strchr(tag_content, '>');
    if (!tag_end) return output_pos;
    
    size_t tag_full_len = tag_end - tag_content + 1;
    
    // For safe tags, copy them (could add attribute filtering here)
    if (output_pos + tag_full_len < max_output_size) {
        memcpy(output + output_pos, tag_content, tag_full_len);
        output_pos += tag_full_len;
    }
    
    return output_pos;
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
    
    size_t input_len = strlen(html);
    char* result = malloc(input_len * 2 + 1); // Extra space for entity encoding
    if (!result) {
        return NULL;
    }
    
    size_t output_pos = 0;
    const char* p = html;
    
    while (*p && output_pos < input_len * 2 - 10) {
        if (*p == '<') {
            // Find end of tag
            const char* tag_end = strchr(p, '>');
            if (tag_end) {
                // Process the tag
                char tag_buffer[1024];
                size_t tag_size = tag_end - p + 1;
                if (tag_size < sizeof(tag_buffer)) {
                    memcpy(tag_buffer, p, tag_size);
                    tag_buffer[tag_size] = '\0';
                    
                    output_pos = process_html_tag(tag_buffer, result, output_pos, input_len * 2);
                }
                p = tag_end + 1;
            } else {
                // Incomplete tag, escape it
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&lt;");
                    output_pos += 4;
                }
                p++;
            }
        } else {
            // Regular character
            if (*p == '&') {
                if (output_pos + 5 < input_len * 2) {
                    strcpy(result + output_pos, "&amp;");
                    output_pos += 5;
                }
            } else if (*p == '>') {
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&gt;");
                    output_pos += 4;
                }
            } else if (*p >= 32 && *p < 127) {
                result[output_pos++] = *p;
            } else {
                // Replace non-printable with space
                result[output_pos++] = ' ';
            }
            p++;
        }
    }
    
    result[output_pos] = '\0';
    return result;
}