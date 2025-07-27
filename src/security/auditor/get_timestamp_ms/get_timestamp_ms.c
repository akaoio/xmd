#define _GNU_SOURCE  // For clock_gettime - must be before includes

/**
 * @file get_timestamp_ms.c
 * @brief Get current timestamp in milliseconds
 * @author XMD Team
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "../../../../include/auditor_internal.h"

/**
 * @brief Get current timestamp in milliseconds
 * @return Current timestamp
 */
uint64_t get_timestamp_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}