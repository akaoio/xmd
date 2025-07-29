/**
 * @file get_memory_usage.c
 * @brief Memory usage retrieval function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include "../../../include/platform.h"

/**
 * @brief Get current memory usage using platform-specific method
 * @return Memory usage in bytes, or -1 on error
 */
uint64_t get_memory_usage(void) {
    return xmd_get_memory_usage();
}