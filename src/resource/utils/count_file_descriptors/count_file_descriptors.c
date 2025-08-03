/**
 * @file count_file_descriptors.c
 * @brief Count file descriptors
 */

#include <dirent.h>
#include <sys/resource.h>
#include "../../../utils/common/common_macros.h"
int count_file_descriptors(void) {
    // Real file descriptor counting implementation
#ifdef __linux__
    int count = 0;
    DIR* fd_dir = opendir("/proc/self/fd");
    if (!fd_dir) {
        return -1;
    }
    struct dirent* entry;
    while ((entry = readdir(fd_dir)) != NULL) {
        // Skip . and .. entries
        if (entry->d_name[0] != '.') {
            count++;
        }
    }
    closedir(fd_dir);
    return count;
#else
    // Fallback for non-Linux systems - use resource limits
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        return (int)limit.rlim_cur;
    }
    return 0;
#endif
}
