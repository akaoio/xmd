/**
 * @file perf_profiler_record_dealloc.c
 * @brief Record memory deallocation
 */

#include <stddef.h>
#include "../../../../include/performance_internal.h"

/**
 * @brief Function implementation
 */
void perf_profiler_record_dealloc(perf_profiler* profiler, size_t size) {
    if (!profiler) return;
    profiler->metrics.deallocations++;
    if (profiler->metrics.memory_current_bytes >= size) {
        profiler->metrics.memory_current_bytes -= size;
    }
}
