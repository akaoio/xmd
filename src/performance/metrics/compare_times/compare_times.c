/**
 * @file compare_times.c
 * @brief Compare function for sorting times
 */

#include <stdint.h>
/**
 * @return Comparison result
 */
int compare_times(const void* a, const void* b) {
    uint64_t time1 = *(const uint64_t*)a;
    uint64_t time2 = *(const uint64_t*)b;
    if (time1 < time2) return -1;
    if (time1 > time2) return 1;
    return 0;
}
