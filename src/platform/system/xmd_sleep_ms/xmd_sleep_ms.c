/**
 * @file xmd_sleep_ms.c
 * @brief Sleep for specified milliseconds
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
/**
 * @brief Sleep for specified milliseconds
 * @param milliseconds Time to sleep
 * @return 0 on success
 */
int xmd_sleep_ms(uint32_t milliseconds) {
#ifdef XMD_PLATFORM_WINDOWS
    Sleep(milliseconds);
    return 0;
#else
    usleep(milliseconds * 1000);
    return 0;
#endif
}
