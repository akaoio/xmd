/**
 * @file xmd_mutex_destroy.c
 * @brief Destroy mutex
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Destroy mutex
 * @param mutex Mutex to destroy
 * @return 0 on success, -1 on error
 */
int xmd_mutex_destroy(xmd_mutex_t* mutex) {
    XMD_VALIDATE_PTRS(-1, mutex);
#ifdef XMD_PLATFORM_WINDOWS
    DeleteCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_destroy(mutex) == 0 ? 0 : -1;
#endif
}
