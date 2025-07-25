/**
 * @file xmd_file_exists.c
 * @brief Check if file exists
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Check if file exists
 * @param path File path
 * @return 1 if exists, 0 if not, -1 on error
 */
int xmd_file_exists(const char* path) {
    if (!path) return -1;
    
#ifdef XMD_PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES) ? 1 : 0;
#else
    return access(path, F_OK) == 0 ? 1 : 0;
#endif
}
