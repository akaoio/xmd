/**
 * @file xmd_get_cpu_count.c
 * @brief Get CPU count
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get CPU count
 * @return Number of CPUs
 */
uint32_t xmd_get_cpu_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
#else
    long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    return cpu_count > 0 ? (uint32_t)cpu_count : 1;
#endif
}
