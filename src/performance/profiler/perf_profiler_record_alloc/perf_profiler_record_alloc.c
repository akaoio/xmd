/**
 * @file perf_profiler_record_alloc.c
 * @brief Record memory allocation
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Record memory allocation
 * @param profiler Profiler instance
 * @param size Size of allocation
 */
void perf_profiler_record_alloc(perf_profiler* profiler, size_t size) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.allocations++;
    profiler->metrics.memory_current_bytes += size;
    
    // Update peak memory
    if (profiler->metrics.memory_current_bytes > profiler->metrics.memory_peak_bytes) {
        profiler->metrics.memory_peak_bytes = profiler->metrics.memory_current_bytes;
    }
}