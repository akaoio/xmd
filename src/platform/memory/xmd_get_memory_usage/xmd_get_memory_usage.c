/**
 * @file xmd_get_memory_usage.c
 * @brief Get current process memory usage
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../../utils/common/validation_macros.h"
/**
 * @brief Get current process memory usage
 * @return Memory usage in bytes
 */
uint64_t xmd_get_memory_usage(void) {
#ifdef XMD_PLATFORM_WINDOWS
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
#elif defined(XMD_PLATFORM_LINUX) && !defined(XMD_PLATFORM_ANDROID)
    FILE* file = fopen("/proc/self/status", "r");
    XMD_VALIDATE_PTR_RETURN(file, 0);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            uint64_t size;
            if (sscanf(line + 6, "%llu", &size) == 1) {
                fclose(file);
                return size * 1024; // Convert KB to bytes
            }
        }
    }
    fclose(file);
#endif
    // Fallback for other platforms
    return 0;
}
