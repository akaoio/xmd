/**
 * @file get_time_ns.c
 * @brief Get current time in nanoseconds
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Get current time in nanoseconds
 * @return Time in nanoseconds
 */
uint64_t get_time_ns(void) {
    xmd_time_t time;
    if (xmd_get_time(&time) != 0) {
        return 0;
    }
    return (uint64_t)time.seconds * 1000000000ULL + (uint64_t)time.nanoseconds;
}