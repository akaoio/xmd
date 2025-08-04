/**
 * @file xmd_mkdir.c
 * @brief Create directory
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "utils/common/common_macros.h"
/**
 * @brief Create directory
 * @param path Directory path
 * @return 0 on success, -1 on error
 */
int xmd_mkdir(const char* path) {
    XMD_VALIDATE_PTRS(-1, path);
#ifdef XMD_PLATFORM_WINDOWS
    return CreateDirectoryA(path, NULL) ? 0 : -1;
#else
    return mkdir(path, 0755) == 0 ? 0 : -1;
#endif
}
