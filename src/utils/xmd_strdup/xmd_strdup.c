/**
 * @file xmd_strdup.c
 * @brief Safe string duplication function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Safe string duplication
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* xmd_strdup(const char* str) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = xmd_malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}