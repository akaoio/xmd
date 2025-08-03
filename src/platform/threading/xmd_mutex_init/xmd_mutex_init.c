/**
 * @file xmd_mutex_init.c
 * @brief Initialize mutex
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Initialize mutex
 * @param mutex Mutex to initialize
 * @return 0 on success, -1 on error
 */
int xmd_mutex_init(xmd_mutex_t* mutex) {
    XMD_VALIDATE_PTRS(-1, mutex);
#ifdef XMD_PLATFORM_WINDOWS
    InitializeCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_init(mutex, NULL) == 0 ? 0 : -1;
#endif
}
