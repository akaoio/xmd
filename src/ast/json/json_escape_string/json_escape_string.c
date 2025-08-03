/**
 * @file json_escape_string.c
 * @brief Implementation of json_escape_string function
 * 
 * This file contains ONLY the json_escape_string function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/utils.h"

/**
 * @brief Escape string for JSON
 * @param str String to escape
 * @return Escaped string (must be freed)
 */
char* json_escape_string(const char* str) {
    if (!str) return xmd_strdup("null");
    
    size_t len = strlen(str);
    size_t max_len = len * 2 + 3; // Worst case: all chars need escaping + quotes
    char* result = xmd_malloc(max_len);
    size_t pos = 0;
    
    result[pos++] = '"';
    
    for (size_t i = 0; i < len; i++) {
        switch (str[i]) {
            case '"':  
                result[pos++] = '\\';
                result[pos++] = '"';
                break;
            case '\\': 
                result[pos++] = '\\';
                result[pos++] = '\\';
                break;
            case '\b': 
                result[pos++] = '\\';
                result[pos++] = 'b';
                break;
            case '\f': 
                result[pos++] = '\\';
                result[pos++] = 'f';
                break;
            case '\n': 
                result[pos++] = '\\';
                result[pos++] = 'n';
                break;
            case '\r': 
                result[pos++] = '\\';
                result[pos++] = 'r';
                break;
            case '\t': 
                result[pos++] = '\\';
                result[pos++] = 't';
                break;
            default:
                if ((unsigned char)str[i] < 0x20) {
                    // Control character - escape as \uXXXX
                    pos += snprintf(result + pos, max_len - pos, "\\u%04x", (unsigned char)str[i]);
                } else {
                    result[pos++] = str[i];
                }
                break;
        }
    }
    
    result[pos++] = '"';
    result[pos] = '\0';
    
    return result;
}
