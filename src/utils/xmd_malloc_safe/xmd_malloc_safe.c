/**
 * @file xmd_malloc_safe.c
 * @brief Safe memory allocation with error logging
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Safe memory allocation with error logging
 * @param size Size to allocate
 * @param error_msg Error message context
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc_safe(size_t size, const char* error_msg) {
    void* ptr = xmd_malloc(size);
    if (!ptr && error_msg) {
        fprintf(stderr, "Memory allocation failed: %s (size: %zu)\n", 
                error_msg, size);
    }
    return ptr;
}