/**
 * @file extract_word.c
 * @brief Word extraction utility function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/import_export.h"

/**
 * @brief Extract word from string
 * @param str String to extract from
 * @param word Output buffer for word (caller must free)
 * @param next Output pointer to next position in string
 * @return Length of extracted word, 0 if no word found
 */
size_t extract_word(const char* str, char** word, const char** next) {
    if (!str || !word) {
        return 0;
    }
    
    str = skip_whitespace(str);
    if (!*str) {
        *word = NULL;
        *next = str;
        return 0;
    }
    
    const char* start = str;
    size_t len = 0;
    
    // Handle quoted strings
    if (*str == '"' || *str == '\'') {
        char quote = *str;
        str++; // Skip opening quote
        start = str;
        
        while (*str && *str != quote) {
            str++;
            len++;
        }
        
        if (*str == quote) {
            str++; // Skip closing quote
        }
    } else {
        // Regular word
        while (*str && !isspace(*str)) {
            str++;
            len++;
        }
    }
    
    if (len > 0) {
        *word = malloc(len + 1);
        if (*word) {
            strncpy(*word, start, len);
            (*word)[len] = '\0';
        }
    } else {
        *word = NULL;
    }
    
    *next = str;
    return len;
}