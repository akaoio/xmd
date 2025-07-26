/**
 * @file xmd_realloc.c
 * @brief Safe realloc function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Safe realloc with NULL check
 * @param ptr Existing pointer
 * @param size New size
 * @return Reallocated memory or NULL on failure
 */
void* xmd_realloc(void* ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    return realloc(ptr, size);
}