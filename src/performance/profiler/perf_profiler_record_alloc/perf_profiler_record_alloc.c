/**
 * @file perf_profiler_record_alloc.c
 * @brief Record memory allocation
 */

#include "../../../../include/performance_internal.h"
#include "../../../../include/platform.h"

/**
 * @brief Record memory allocation
 * @param profiler Performance profiler
 * @param size Size of allocation
 */
void perf_profiler_record_alloc(perf_profiler* profiler, size_t size) {
    if (!profiler) return;
    profiler->metrics.allocations++;
    profiler->metrics.memory_current_bytes += size;
    if (profiler->metrics.memory_current_bytes > profiler->metrics.memory_peak_bytes) {
        profiler->metrics.memory_peak_bytes = profiler->metrics.memory_current_bytes;
    }
}
