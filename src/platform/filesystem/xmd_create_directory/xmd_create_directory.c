/**
 * @file xmd_create_directory.c
 * @brief Create directory with error checking
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create directory with error checking
 * @param path Directory path
 * @return 0 on success, -1 on error
 */
int xmd_create_directory(const char* path) {
    XMD_VALIDATE_PTRS(-1, path);
    // Check if directory already exists
    if (xmd_is_directory(path) == 1) {
        return 0; // Already exists
    }
    return xmd_mkdir(path);
}
