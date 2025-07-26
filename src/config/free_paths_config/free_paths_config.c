/**
 * @file free_paths_config.c
 * @brief Free paths configuration function
 * @author XMD Team
 *
 * Implementation of paths configuration cleanup for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Free paths configuration
 * @param paths Paths configuration to free
 */
void free_paths_config(xmd_paths_config* paths) {
    free(paths->proc_status_path);
    free(paths->proc_fd_path);
    free(paths->temp_dir);
    
    for (size_t i = 0; i < paths->module_search_path_count; i++) {
        free(paths->module_search_paths[i]);
    }
    free(paths->module_search_paths);
}