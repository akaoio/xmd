/**
 * @file perf_profiler_record_cache_miss.c
 * @brief Record cache miss
 */

#include "../../../../include/performance_internal.h"
void perf_profiler_record_cache_miss(perf_profiler* profiler) {
    if (!profiler) return;
    profiler->metrics.cache_misses++;
}
