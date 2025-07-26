/**
 * @file xmd_get_tick_count.c
 * @brief Get tick count in milliseconds
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get tick count in milliseconds
 * @return Tick count in milliseconds
 */
uint64_t xmd_get_tick_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    return GetTickCount64();
#else
    xmd_time_t time;
    if (xmd_get_time(&time) != 0) return 0;
    return (uint64_t)time.seconds * 1000 + time.nanoseconds / 1000000;
#endif
}
