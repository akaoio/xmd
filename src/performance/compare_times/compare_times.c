/**
 * @file compare_times.c
 * @brief Time comparison function for sorting
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdint.h>

/**
 * @brief Compare function for sorting benchmark times
 * @param a First time value
 * @param b Second time value
 * @return Comparison result
 */
int compare_times(const void* a, const void* b) {
    uint64_t time_a = *(const uint64_t*)a;
    uint64_t time_b = *(const uint64_t*)b;
    
    if (time_a < time_b) return -1;
    if (time_a > time_b) return 1;
    return 0;
}