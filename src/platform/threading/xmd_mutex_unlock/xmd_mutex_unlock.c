/**
 * @file xmd_mutex_unlock.c
 * @brief Unlock mutex
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
/**
 * @brief Unlock mutex
 * @param mutex Mutex to unlock
 * @return 0 on success, -1 on error
 */
int xmd_mutex_unlock(xmd_mutex_t* mutex) {
    if (!mutex) return -1;
#ifdef XMD_PLATFORM_WINDOWS
    LeaveCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_unlock(mutex) == 0 ? 0 : -1;
#endif
}
