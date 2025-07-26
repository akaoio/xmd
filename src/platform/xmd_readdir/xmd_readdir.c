/**
 * @file xmd_readdir.c
 * @brief Read directory entry
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Read directory entry
 * @param dir Directory handle
 * @return Directory entry or NULL on end/error
 */
xmd_dirent_t* xmd_readdir(xmd_dir_t dir) {
    if (dir == XMD_INVALID_DIR) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    static struct _finddata_t entry;
    if (_findnext(dir, &entry) == 0) {
        return &entry;
    }
    return NULL;
#else
    return readdir(dir);
#endif
}
