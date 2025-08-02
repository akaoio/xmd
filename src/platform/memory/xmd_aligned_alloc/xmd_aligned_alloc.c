/**
 * @file xmd_aligned_alloc.c
 * @brief Allocate aligned memory
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
/**
 * @brief Allocate aligned memory using C17 compatible approach
 * @param alignment Memory alignment
 * @param size Size to allocate
 * @return Aligned memory or NULL on error
 */
void* xmd_aligned_alloc(size_t alignment, size_t size) {
#ifdef XMD_PLATFORM_WINDOWS
    return _aligned_xmd_malloc(size, alignment);
#else
    /* Use POSIX approach for all Unix-like systems including Android/Linux */
    void* ptr;
    if (posix_memalign(&ptr, alignment, size) == 0) {
        return ptr;
    }
    return NULL;
#endif
}
