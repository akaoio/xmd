/**
 * @file xmd_calloc.c
 * @brief Safe calloc wrapper
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "../../../../include/utils.h"
/**
 * @brief Safe calloc wrapper
 * @param count Number of elements
 * @param size Size of each element
 * @return Allocated zeroed memory or NULL on failure
 */
void* xmd_calloc(size_t count, size_t size) {
    if (count == 0 || size == 0) {
        return NULL;
    }
    return calloc(count, size);
}
