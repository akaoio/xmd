/**
 * @file xmd_closedir.c
 * @brief Close directory
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Close directory
 * @param dir Directory handle
 */
void xmd_closedir(xmd_dir_t dir) {
    if (dir == XMD_INVALID_DIR) return;
    
#ifdef XMD_PLATFORM_WINDOWS
    _findclose(dir);
#else
    closedir(dir);
#endif
}
