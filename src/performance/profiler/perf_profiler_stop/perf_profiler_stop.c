/**
 * @file perf_profiler_stop.c
 * @brief Stop profiling session
 */

#include "../../../../include/performance_internal.h"
#include "../../../../include/platform.h"

/**
 * @brief Stop profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_stop(perf_profiler* profiler) {
    if (!profiler || !profiler->is_active) return -1;
    
    xmd_get_time(&profiler->end_time);
    profiler->is_active = false;
    
    return 0;
}
