/**
 * @file xmd_malloc.c
 * @brief Safe memory allocation with error checking
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief Safe memory allocation with error checking
 * @param size Size to allocate
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc(size_t size) {
    if (size == 0) {
        printf("[ERROR] xmd_malloc: Zero size allocation requested\n");
        return NULL;
    }
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
    }
    return ptr;
}
