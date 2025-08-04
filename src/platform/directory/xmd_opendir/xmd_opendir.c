/**
 * @file xmd_opendir.c
 * @brief Open directory for reading
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Open directory for reading
 * @param path Directory path
 * @return Directory handle or XMD_INVALID_DIR on error
 */
xmd_dir_t xmd_opendir(const char* path) {
    XMD_VALIDATE_PTR_RETURN(path, XMD_INVALID_DIR);
#ifdef XMD_PLATFORM_WINDOWS
    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    struct _finddata_t* finddata;
    XMD_MALLOC_DYNAMIC(finddata, sizeof(struct _finddata_t), XMD_INVALID_DIR);
    return _findfirst(search_path, finddata);
#else
    return opendir(path);
#endif
}
