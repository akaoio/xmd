/**
 * @file xmd_get_time.c
 * @brief Get current high-resolution time
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get current high-resolution time
 * @param time Output time structure
 * @return 0 on success, -1 on error
 */
int xmd_get_time(xmd_time_t* time) {
    if (!time) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    LARGE_INTEGER freq, counter;
    if (!QueryPerformanceFrequency(&freq) || !QueryPerformanceCounter(&counter)) {
        return -1;
    }
    time->seconds = counter.QuadPart / freq.QuadPart;
    time->nanoseconds = ((counter.QuadPart % freq.QuadPart) * 1000000000LL) / freq.QuadPart;
#else
    struct timespec ts;
    #ifdef XMD_PLATFORM_MACOS
        clock_gettime(CLOCK_UPTIME_RAW, &ts);
    #else
        clock_gettime(CLOCK_MONOTONIC, &ts);
    #endif
    time->seconds = ts.tv_sec;
    time->nanoseconds = ts.tv_nsec;
#endif
    
    return 0;
}
