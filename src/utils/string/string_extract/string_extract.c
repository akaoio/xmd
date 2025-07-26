/**
 * @file string_extract.c
 * @brief Implementation of string extraction utility
 * 
 * Provides safe substring extraction with bounds checking.
 */

#include <stdlib.h>
#include <string.h>
#include "string_extract.h"

/**
 * @brief Extract a substring from a string
 * 
 * Extracts a substring starting at the given position with the specified length.
 * The returned string is null-terminated and must be freed by the caller.
 * If the requested length extends beyond the string, only available characters are extracted.
 * 
 * @param str The source string
 * @param start Starting position (0-based)
 * @param length Number of characters to extract
 * @return New substring on success, NULL if str is NULL, start is out of bounds, or allocation fails
 */
char* string_extract(const char* str, size_t start, size_t length) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t str_len = strlen(str);
    
    // Check if start is out of bounds
    if (start >= str_len) {
        return NULL;
    }
    
    // Adjust length if it extends beyond string end
    size_t available = str_len - start;
    if (length > available) {
        length = available;
    }
    
    // Allocate memory for substring
    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // Copy substring
    memcpy(result, str + start, length);
    result[length] = '\0';
    
    return result;
}
