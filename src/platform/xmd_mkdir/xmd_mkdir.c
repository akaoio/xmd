/**
 * @file xmd_mkdir.c
 * @brief Create directory
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Create directory
 * @param path Directory path
 * @return 0 on success, -1 on error
 */
int xmd_mkdir(const char* path) {
    if (!path) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    return CreateDirectoryA(path, NULL) ? 0 : -1;
#else
    return mkdir(path, 0755) == 0 ? 0 : -1;
#endif
}
