/**
 * @file calculate_stats.c
 * @brief Calculate statistics from timing data
 */

#include <stdlib.h>
#include <stdint.h>
#include "../../../../include/performance_internal.h"

int compare_times(const void* a, const void* b);
/**
 * @param result Benchmark result to populate
 */
void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result) {
    if (!times || !count || !result) {
        return;
    }
    
    // Sort times
    qsort(times, count, sizeof(uint64_t), compare_times);
    
    // Calculate min, max, median
    result->min_time_ns = times[0];
    result->max_time_ns = times[count - 1];
    result->median_time_ns = times[count / 2];
    
    // Calculate average
    uint64_t total = 0;
    for (uint32_t i = 0; i < count; i++) {
        total += times[i];
    }
    result->avg_time_ns = total / count;
    
    // Calculate throughput
    if (result->avg_time_ns > 0) {
        result->throughput_ops_per_sec = 1000000000.0 / result->avg_time_ns;
    }
}
