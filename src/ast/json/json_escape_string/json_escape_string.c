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
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Escape string for JSON
 * @param str String to escape
 * @return Escaped string (must be freed)
 */
char* json_escape_string(const char* str) {
    XMD_VALIDATE_PTRS(xmd_strdup("null"), str);
    
    size_t len = strlen(str);
    size_t max_len = len * 2 + 3; // Worst case: all chars need escaping + quotes
    char* result;
    XMD_MALLOC_DYNAMIC(result, max_len, xmd_strdup("null"));
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
