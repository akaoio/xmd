/**
 * @file perf_profiler_record_dealloc.c
 * @brief Record memory deallocation
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Record memory deallocation
 * @param profiler Profiler instance
 * @param size Size of deallocation
 */
void perf_profiler_record_dealloc(perf_profiler* profiler, size_t size) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.deallocations++;
    if (profiler->metrics.memory_current_bytes >= size) {
        profiler->metrics.memory_current_bytes -= size;
    }
}