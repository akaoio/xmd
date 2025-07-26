/**
 * @file xmd_calloc.c
 * @brief Safe calloc function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Safe calloc with NULL check
 * @param count Number of elements
 * @param size Size of each element
 * @return Allocated and zeroed memory or NULL on failure
 */
void* xmd_calloc(size_t count, size_t size) {
    if (count == 0 || size == 0) {
        return NULL;
    }
    return calloc(count, size);
}