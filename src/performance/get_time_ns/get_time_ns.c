#define _GNU_SOURCE  // For clock_gettime - must be before includes

/**
 * @file get_time_ns.c
 * @brief High-resolution time measurement function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "../../../include/performance.h"

/**
 * @brief Get current time in nanoseconds
 * @return Time in nanoseconds
 */
uint64_t get_time_ns(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}