/**
 * @file xmd_sleep_ms.c
 * @brief Sleep for specified milliseconds
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Sleep for specified milliseconds
 * @param milliseconds Time to sleep
 * @return 0 on success, -1 on error
 */
int xmd_sleep_ms(uint32_t milliseconds) {
#ifdef XMD_PLATFORM_WINDOWS
    Sleep(milliseconds);
    return 0;
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&ts, NULL) == 0 ? 0 : -1;
#endif
}
