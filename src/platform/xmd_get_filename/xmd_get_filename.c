/**
 * @file xmd_get_filename.c
 * @brief Get filename from directory entry
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Get filename from directory entry
 * @param entry Directory entry
 * @return Filename or NULL on error
 */
char* xmd_get_filename(xmd_dirent_t* entry) {
    if (!entry) return NULL;
    
#ifdef XMD_PLATFORM_WINDOWS
    return entry->name;
#else
    return entry->d_name;
#endif
}
