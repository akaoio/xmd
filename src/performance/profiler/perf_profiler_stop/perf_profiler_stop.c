/**
 * @file perf_profiler_stop.c
 * @brief Stop profiling session
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Stop profiling session
 * @param profiler Profiler instance
 * @return 0 on success, -1 on error
 */
int perf_profiler_stop(perf_profiler* profiler) {
    if (!profiler || !profiler->is_active) {
        return -1;
    }
    
    // Record end time
    if (xmd_get_time(&profiler->end_time) != 0) {
        return -1;
    }
    
    // Calculate execution time
    profiler->metrics.execution_time_ns = time_diff_ns(&profiler->start_time, &profiler->end_time);
    
    // Update current memory usage
    uint64_t current_memory = get_memory_usage();
    profiler->metrics.memory_current_bytes = current_memory;
    
    // Update peak memory if current is higher
    if (current_memory > profiler->metrics.memory_peak_bytes) {
        profiler->metrics.memory_peak_bytes = current_memory;
    }
    
    profiler->is_active = false;
    return 0;
}