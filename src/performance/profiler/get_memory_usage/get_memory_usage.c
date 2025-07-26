/**
 * @file get_memory_usage.c
 * @brief Get current memory usage wrapper
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Get current memory usage using platform-specific method
 * @return Memory usage in bytes or 0 if unavailable
 */
uint64_t get_memory_usage(void) {
    uint64_t mem = xmd_get_memory_usage();
    return mem;
}