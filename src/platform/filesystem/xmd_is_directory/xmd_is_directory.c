/**
 * @file xmd_is_directory.c
 * @brief Check if path is directory
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Check if path is directory
 * @param path Path to check
 * @return 1 if directory, 0 if not, -1 on error
 */
int xmd_is_directory(const char* path) {
    XMD_VALIDATE_PTRS(-1, path);
#ifdef XMD_PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    if (attrs == INVALID_FILE_ATTRIBUTES) return -1;
    return (attrs & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
#else
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return S_ISDIR(st.st_mode) ? 1 : 0;
#endif
}
