/**
 * @file xmd_aligned_free.c
 * @brief Free aligned memory
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Free aligned memory
 * @param ptr Memory to free
 */
void xmd_aligned_free(void* ptr) {
    if (!ptr) return;
#ifdef XMD_PLATFORM_WINDOWS
    _aligned_free(ptr);
#else
    XMD_FREE_SAFE(ptr);
#endif
}
