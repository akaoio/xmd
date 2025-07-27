/**
 * @file skip_whitespace.c
 * @brief Whitespace skipping utility function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <ctype.h>

/**
 * @brief Skip whitespace in string
 * @param str String pointer
 * @return Pointer to first non-whitespace character
 */
const char* skip_whitespace(const char* str) {
    while (str && isspace(*str)) {
        str++;
    }
    return str;
}