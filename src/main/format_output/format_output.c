/**
 * @file format_output.c
 * @brief Output formatting function
 * @author XMD Team
 *
 * Implementation of output formatting for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Format output according to specified format
 * @param content Raw processed content
 * @param format Output format ("markdown", "html", "json")
 * @param formatted_output Buffer to store formatted output
 * @param buffer_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int format_output(const char* content, const char* format, char* formatted_output, size_t buffer_size) {
    if (!content || !format || !formatted_output || buffer_size == 0) {
        return -1;
    }
    
    if (strcmp(format, "markdown") == 0) {
        // Markdown format - output as-is (default)
        if (strlen(content) >= buffer_size) {
            return -1;
        }
        strcpy(formatted_output, content);
        return 0;
    } 
    else if (strcmp(format, "html") == 0) {
        // HTML format - wrap in basic HTML structure and convert markdown
        int written = snprintf(formatted_output, buffer_size,
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <meta charset=\"UTF-8\">\n"
            "    <title>XMD Output</title>\n"
            "    <style>\n"
            "        body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; }\n"
            "        pre { background: #f5f5f5; padding: 1em; border-radius: 4px; }\n"
            "        code { background: #f0f0f0; padding: 2px 4px; border-radius: 2px; }\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "<div class=\"xmd-content\">\n"
            "%s\n"
            "</div>\n"
            "</body>\n"
            "</html>\n", 
            content);
        return (written < 0 || written >= buffer_size) ? -1 : 0;
    }
    else if (strcmp(format, "json") == 0) {
        // JSON format - wrap content in JSON structure
        // Escape quotes and newlines in content
        char escaped_content[buffer_size / 2];
        const char* src = content;
        char* dst = escaped_content;
        size_t remaining = sizeof(escaped_content) - 1;
        
        while (*src && remaining > 2) {
            if (*src == '"') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = '"';
                remaining -= 2;
            } else if (*src == '\\') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = '\\';
                remaining -= 2;
            } else if (*src == '\n') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 'n';
                remaining -= 2;
            } else if (*src == '\r') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 'r';
                remaining -= 2;
            } else if (*src == '\t') {
                if (remaining < 2) break;
                *dst++ = '\\';
                *dst++ = 't';
                remaining -= 2;
            } else {
                *dst++ = *src;
                remaining--;
            }
            src++;
        }
        *dst = '\0';
        
        int written = snprintf(formatted_output, buffer_size,
            "{\n"
            "  \"status\": \"success\",\n"
            "  \"format\": \"json\",\n"
            "  \"processor\": \"XMD v%s\",\n"
            "  \"content\": \"%s\"\n"
            "}\n",
            xmd_get_version(), escaped_content);
        return (written < 0 || written >= buffer_size) ? -1 : 0;
    }
    
    return -1; // Unknown format
}