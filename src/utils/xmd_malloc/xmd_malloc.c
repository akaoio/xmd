/**
 * @file xmd_malloc.c
 * @brief Safe memory allocation function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Safe malloc with NULL check
 * @param size Size to allocate
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    return malloc(size);
}