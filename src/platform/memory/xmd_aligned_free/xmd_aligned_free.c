/**
 * @file xmd_aligned_free.c
 * @brief Free aligned memory
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
/**
 * @brief Free aligned memory
 * @param ptr Memory to free
 */
void xmd_aligned_XMD_FREE_SAFE(void* ptr) {
    if (!ptr) return;
#ifdef XMD_PLATFORM_WINDOWS
    _aligned_XMD_FREE_SAFE(ptr);
#else
    XMD_FREE_SAFE(ptr);
#endif
}
