/**
 * @file perf_profiler_start.c
 * @brief Start profiling session
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Start profiling session
 * @param profiler Profiler instance
 * @return 0 on success, -1 on error
 */
int perf_profiler_start(perf_profiler* profiler) {
    if (!profiler) {
        return -1;
    }
    
    if (profiler->is_active) {
        return -1; // Already active
    }
    
    // Record start time
    if (xmd_get_time(&profiler->start_time) != 0) {
        return -1;
    }
    
    // Reset metrics for new session
    memset(&profiler->metrics, 0, sizeof(perf_metrics));
    profiler->metrics.memory_current_bytes = get_memory_usage();
    profiler->is_active = true;
    
    return 0;
}