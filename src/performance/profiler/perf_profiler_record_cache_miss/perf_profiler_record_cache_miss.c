/**
 * @file perf_profiler_record_cache_miss.c
 * @brief Record cache miss
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Record cache miss
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_miss(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.cache_misses++;
}