/**
 * @file perf_profiler_start.c
 * @brief Start profiling session
 */

#include "../../../../include/performance_internal.h"
#include "../../../../include/platform.h"

/**
 * @brief FUNCTION_Start profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_start(perf_profiler* profiler) {
    if (!profiler) return -1;
    xmd_get_time(&profiler->start_time);
    profiler->is_active = true;
    return 0;
}
