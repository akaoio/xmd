/**
 * @file xmd_config_free.c
 * @brief Free XMD configuration
 * 
 * This file contains ONLY the xmd_config_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/config_internal.h"
/**
 * @brief Free XMD configuration
 * @param config Configuration to free
  * /
 */
void xmd_config_XMD_FREE_SAFE(xmd_config* config) {
    if (!config) return;
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    // Free path strings
    XMD_FREE_SAFE(internal->paths.proc_status_path);
    XMD_FREE_SAFE(internal->paths.proc_fd_path);
    XMD_FREE_SAFE(internal->paths.temp_dir);
    
    // Free module search paths if they exist
    if (internal->paths.module_search_paths) {
        for (size_t i = 0; i < internal->paths.module_search_path_count; i++) {
            XMD_FREE_SAFE(internal->paths.module_search_paths[i]);
        }
        XMD_FREE_SAFE(internal->paths.module_search_paths);
    }
    
    // Free security exec whitelist
    if (internal->security.exec_whitelist) {
        for (size_t i = 0; i < internal->security.exec_whitelist_count; i++) {
            XMD_FREE_SAFE(internal->security.exec_whitelist[i]);
        }
        XMD_FREE_SAFE(internal->security.exec_whitelist);
    }
    
    XMD_FREE_SAFE(config);
}
