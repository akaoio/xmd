/**
 * @file xmd_internal_config_free.c
 * @brief Free internal configuration and all allocated resources
 * 
 * This file contains ONLY the xmd_internal_config_free function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "utils/common/common_macros.h"
#include <stdlib.h>

/**
 * @brief Free internal configuration and all allocated resources
 * @param config Configuration to free
 */
void xmd_internal_config_free(xmd_internal_config* config) {
    XMD_ENTRY_VALIDATE_VOID(config);
    
    // Free paths configuration
    XMD_FREE_SAFE(config->paths.proc_status_path);
    XMD_FREE_SAFE(config->paths.proc_fd_path);
    XMD_FREE_SAFE(config->paths.temp_dir);
    
    // Free module search paths
    if (config->paths.module_search_paths) {
        for (size_t i = 0; i < config->paths.module_search_path_count; i++) {
            XMD_FREE_SAFE(config->paths.module_search_paths[i]);
        }
        XMD_FREE_SAFE(config->paths.module_search_paths);
    }
    
    // Free security configuration
    if (config->security.exec_whitelist) {
        for (size_t i = 0; i < config->security.exec_whitelist_count; i++) {
            XMD_FREE_SAFE(config->security.exec_whitelist[i]);
        }
        XMD_FREE_SAFE(config->security.exec_whitelist);
    }
    
    // Free precision format string (cast away const for cleanup)
    char* format_copy = (char*)config->precision.number_format;
    XMD_FREE_SAFE(format_copy);
    
    // Free config file path
    XMD_FREE_SAFE(config->config_file_path);
    
    // Free the configuration structure itself
    XMD_FREE_SAFE(config);
}