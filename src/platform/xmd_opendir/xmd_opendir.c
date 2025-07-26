/**
 * @file xmd_opendir.c
 * @brief Open directory for reading
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Open directory for reading
 * @param path Directory path
 * @return Directory handle or XMD_INVALID_DIR on error
 */
xmd_dir_t xmd_opendir(const char* path) {
    if (!path) return XMD_INVALID_DIR;
    
#ifdef XMD_PLATFORM_WINDOWS
    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    return _findfirst(search_path, (struct _finddata_t*)malloc(sizeof(struct _finddata_t)));
#else
    return opendir(path);
#endif
}
