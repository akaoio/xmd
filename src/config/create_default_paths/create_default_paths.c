/**
 * @file create_default_paths.c
 * @brief Default paths configuration creation function
 * @author XMD Team
 *
 * Implementation of default paths configuration creation for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/config_internal.h"

/**
 * @brief Create default paths configuration
 * @return Default paths configuration
 */
xmd_paths_config create_default_paths(void) {
    xmd_paths_config paths = {
        .proc_status_path = strdup("/proc/self/status"),
        .proc_fd_path = strdup("/proc/self/fd"),
        .temp_dir = strdup("/tmp"),
        .module_search_paths = NULL,
        .module_search_path_count = 0
    };
    return paths;
}
