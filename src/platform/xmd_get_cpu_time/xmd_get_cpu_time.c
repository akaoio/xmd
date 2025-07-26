/**
 * @file xmd_get_cpu_time.c
 * @brief Get current CPU time for process
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get current CPU time for process
 * @return CPU time in milliseconds
 */
long xmd_get_cpu_time(void) {
#ifdef XMD_PLATFORM_WINDOWS
    FILETIME creation, exit, kernel, user;
    if (GetProcessTimes(GetCurrentProcess(), &creation, &exit, &kernel, &user)) {
        ULARGE_INTEGER k, u;
        k.LowPart = kernel.dwLowDateTime;
        k.HighPart = kernel.dwHighDateTime;
        u.LowPart = user.dwLowDateTime;
        u.HighPart = user.dwHighDateTime;
        // Convert 100-nanosecond intervals to milliseconds
        return (long)((k.QuadPart + u.QuadPart) / 10000);
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) * 1000 +
               (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000;
    }
    return 0;
#endif
}
