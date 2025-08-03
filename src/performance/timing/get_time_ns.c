/**
 * @file get_time_ns.c
 * @brief Get current time in nanoseconds
 */

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdint.h>
uint64_t get_time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}
