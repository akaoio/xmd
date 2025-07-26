/**
 * @file xmd_aligned_free.c
 * @brief Free aligned memory
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Free aligned memory
 * @param ptr Memory to free
 */
void xmd_aligned_free(void* ptr) {
    if (!ptr) return;
    
#ifdef XMD_PLATFORM_WINDOWS
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}
