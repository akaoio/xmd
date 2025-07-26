/**
 * @file xmd_get_fd_count.c
 * @brief Get file descriptor count for current process
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get file descriptor count for current process
 * @return Number of open file descriptors
 */
int xmd_get_fd_count(void) {
#ifdef XMD_PLATFORM_WINDOWS
    // Windows doesn't have a simple way to count handles
    // Return a default estimate
    return 10;
#elif defined(XMD_PLATFORM_LINUX) && !defined(XMD_PLATFORM_ANDROID)
    DIR* fd_dir = opendir("/proc/self/fd");
    if (!fd_dir) return -1;
    
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(fd_dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            count++;
        }
    }
    closedir(fd_dir);
    return count;
#else
    // Fallback for other platforms
    return 10;
#endif
}
