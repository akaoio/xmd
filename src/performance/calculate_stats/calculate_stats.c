/**
 * @file calculate_stats.c
 * @brief Benchmark statistics calculation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../../include/performance.h"

/**
 * @brief Calculate statistics from timing data
 * @param times Array of timing measurements
 * @param count Number of measurements
 * @param result Result structure to populate
 */
void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result) {
    if (!times || count == 0 || !result) {
        return;
    }
    
    // Sort times for median calculation
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
    
    // Calculate throughput (operations per second)
    if (result->avg_time_ns > 0) {
        result->throughput_ops_per_sec = 1000000000.0 / result->avg_time_ns;
    } else {
        result->throughput_ops_per_sec = 0.0;
    }
    
    result->iterations = count;
}