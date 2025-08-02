/**
 * @file perf_profiler_generate_report.c
 * @brief Generate profiler report
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "../../../../include/utils.h"

/**
 * @brief Function implementation
 */
char* perf_profiler_generate_report(perf_profiler* profiler) {
    if (!profiler) return NULL;
    
    char* report = xmd_malloc(2048);
    if (!report) return NULL;
    
    int64_t diff_seconds = profiler->end_time.seconds - profiler->start_time.seconds;
    int64_t diff_nanoseconds = profiler->end_time.nanoseconds - profiler->start_time.nanoseconds;
    uint64_t total_time = (uint64_t)(diff_seconds * 1000000000ULL + diff_nanoseconds);
    
    snprintf(report, 2048,
        "Performance Profile Report\n"
        "==========================\n"
        "Total Time: %lu ns (%.2f ms)\n"
        "Allocations: %u (Peak: %.2f MB)\n"
        "Deallocations: %u (Current: %.2f MB)\n"
        "Cache Hits: %u, Misses: %u\n",
        total_time, total_time / 1000000.0,
        profiler->metrics.allocations, profiler->metrics.memory_peak_bytes / (1024.0 * 1024.0),
        profiler->metrics.deallocations, profiler->metrics.memory_current_bytes / (1024.0 * 1024.0),
        profiler->metrics.cache_hits, profiler->metrics.cache_misses);
    
    return report;
}
