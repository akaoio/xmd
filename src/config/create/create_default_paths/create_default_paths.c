/**
 * @file create_default_paths.c
 * @brief Create default file paths
 * 
 * This file contains ONLY the create_default_paths function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"
#include "../../../../include/utils.h"

/**
 * @brief Create default file paths
 * @return Default paths configuration
 */
xmd_paths_config create_default_paths(void) {
    xmd_paths_config paths;
    
    // Initialize paths according to actual struct definition
    paths.proc_status_path = xmd_strdup("/proc/self/status");
    paths.proc_fd_path = xmd_strdup("/proc/self/fd"); 
    paths.temp_dir = xmd_strdup("/tmp");
    paths.module_search_paths = NULL;
    paths.module_search_path_count = 0;
    
    return paths;
}
