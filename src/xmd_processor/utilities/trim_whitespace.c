/**
 * @file trim_whitespace.c
 * @brief Trim whitespace from string implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Trim whitespace from string
 * @param str Input string to trim (modified in place)
 * @return Pointer to trimmed string
 */
char* trim_whitespace(char* str) {
    if (!str) return str;
    
    while (*str && isspace(*str)) str++;
    
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    return str;
}
