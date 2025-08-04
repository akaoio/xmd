/**
 * @file xmd_mutex_lock.c
 * @brief Lock mutex
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "utils/common/common_macros.h"
/**
 * @brief Lock mutex
 * @param mutex Mutex to lock
 * @return 0 on success, -1 on error
 */
int xmd_mutex_lock(xmd_mutex_t* mutex) {
    XMD_VALIDATE_PTRS(-1, mutex);
#ifdef XMD_PLATFORM_WINDOWS
    EnterCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_lock(mutex) == 0 ? 0 : -1;
#endif
}
