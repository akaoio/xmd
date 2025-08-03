/**
 * @file xmd_realloc.c
 * @brief Safe realloc wrapper
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "../../../../include/utils.h"
#include "../../common/common_macros.h"
/**
 * @brief Safe realloc wrapper
 * @param ptr Pointer to reallocate
 * @param size New size
 * @return Reallocated memory or NULL on failure
 */
void* xmd_realloc(void* ptr, size_t size) {
    if (size == 0) {
        if (ptr) {
            free(ptr);
        }
        return NULL;
    }
    return realloc(ptr, size);
}
