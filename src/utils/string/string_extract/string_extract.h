/**
 * @file string_extract.h
 * @brief String extraction utility
 * 
 * Provides safe substring extraction with bounds checking.
 */

#ifndef STRING_EXTRACT_H
#define STRING_EXTRACT_H

#include <stddef.h>

/**
 * @brief Extract a substring from a string
 * 
 * Extracts a substring starting at the given position with the specified length.
 * The returned string is null-terminated and must be freed by the caller.
 * 
 * @param str The source string
 * @param start Starting position (0-based)
 * @param length Number of characters to extract
 * @return New substring on success, NULL if str is NULL, start is out of bounds, or allocation fails
 */
char* string_extract(const char* str, size_t start, size_t length);

#endif /* STRING_EXTRACT_H */