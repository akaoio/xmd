/**
 * @file perf_profiler_record_cache_hit.c
 * @brief Record cache hit
 */

#include "../../../../include/performance_internal.h"
void perf_profiler_record_cache_hit(perf_profiler* profiler) {
    if (!profiler) return;
    profiler->metrics.cache_hits++;
}
