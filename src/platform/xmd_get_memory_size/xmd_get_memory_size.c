/**
 * @file xmd_get_memory_size.c
 * @brief Get total system memory
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get total system memory
 * @return Memory size in bytes
 */
uint64_t xmd_get_memory_size(void) {
#ifdef XMD_PLATFORM_WINDOWS
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        return status.ullTotalPhys;
    }
    return 0;
#else
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (pages > 0 && page_size > 0) {
        return (uint64_t)pages * page_size;
    }
    return 0;
#endif
}
