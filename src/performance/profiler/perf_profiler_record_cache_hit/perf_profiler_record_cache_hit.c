/**
 * @file perf_profiler_record_cache_hit.c
 * @brief Record cache hit
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Record cache hit
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_hit(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.cache_hits++;
}