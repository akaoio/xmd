/**
 * @file config_destroy.c
 * @brief Implementation of config_destroy function
 * 
 * This file contains ONLY the config_destroy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/xmd.h"
#include <stdlib.h>

/**
 * @brief Free configuration and all associated resources
 * @param config Configuration to free
 */
void config_destroy(xmd_config* config) {
    if (!config) return;
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    // Free path strings (only the ones that exist in the struct)
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
