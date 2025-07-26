/**
 * @file time_diff_ns.c
 * @brief Calculate time difference in nanoseconds
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Calculate time difference in nanoseconds
 * @param start Start time
 * @param end End time
 * @return Difference in nanoseconds
 */
uint64_t time_diff_ns(const xmd_time_t* start, const xmd_time_t* end) {
    uint64_t start_ns = (uint64_t)start->seconds * 1000000000ULL + (uint64_t)start->nanoseconds;
    uint64_t end_ns = (uint64_t)end->seconds * 1000000000ULL + (uint64_t)end->nanoseconds;
    return end_ns - start_ns;
}