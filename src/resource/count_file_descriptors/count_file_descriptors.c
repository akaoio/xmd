/**
 * @file count_file_descriptors.c
 * @brief File descriptor counting function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include "../../../include/platform.h"

/**
 * @brief Count open file descriptors using platform-specific method
 * @return Number of open file descriptors, or -1 on error
 */
int count_file_descriptors(void) {
    return xmd_get_fd_count();
}