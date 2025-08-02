/**
 * @file string_extract.c
 * @brief Extract substring from string
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <stddef.h>
#include "../../../../include/utils.h"
/**
 * @brief Extract substring from string
 * @param source Source string
 * @param start Start position
 * @param length Length to extract
 * @return Extracted string or NULL on failure
 */
char* string_extract(const char* source, size_t start, size_t length) {
    if (!source) {
        return NULL;
    }
    size_t source_len = strlen(source);
    if (start >= source_len) {
        return NULL;
    }
    // Adjust length if it exceeds remaining string
    if (start + length > source_len) {
        length = source_len - start;
    }
    char* extracted = xmd_malloc(length + 1);
    if (!extracted) {
        return NULL;
    }
    strncpy(extracted, source + start, length);
    extracted[length] = '\0';
    return extracted;
}
