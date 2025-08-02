/**
 * @file is_safe_html_tag.c
 * @brief Check if HTML tag is in whitelist of safe tags
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security utilities subsystem
 */

#include <stdbool.h>
#include <string.h>
#include <strings.h>
/**
 * @brief Check if tag is in whitelist of safe HTML tags
 * @param tag Tag name to check
 * @return true if tag is safe
 */
bool is_safe_html_tag(const char* tag) {
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
