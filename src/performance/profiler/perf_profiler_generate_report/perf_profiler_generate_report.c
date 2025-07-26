/**
 * @file perf_profiler_generate_report.c
 * @brief Generate profiling report
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Generate profiling report
 * @param profiler Profiler instance
 * @return Report string (must be freed) or NULL on error
 */
char* perf_profiler_generate_report(perf_profiler* profiler) {
    if (!profiler) {
        return NULL;
    }
    
    const size_t report_size = 2048;
    char* report = malloc(report_size);
    if (!report) {
        return NULL;
    }
    
    const perf_metrics* metrics = &profiler->metrics;
    
    // Calculate cache hit rate
    uint32_t total_cache_accesses = metrics->cache_hits + metrics->cache_misses;
    double cache_hit_rate = 0.0;
    if (total_cache_accesses > 0) {
        cache_hit_rate = (double)metrics->cache_hits / total_cache_accesses * 100.0;
    }
    
    // Calculate memory efficiency
    uint32_t total_allocations = metrics->allocations + metrics->deallocations;
    double alloc_efficiency = 0.0;
    if (total_allocations > 0) {
        alloc_efficiency = (double)metrics->deallocations / metrics->allocations * 100.0;
    }
    
    snprintf(report, report_size,
        "=== Performance Profile Report ===\n"
        "\n"
        "Timing:\n"
        "  Execution Time: %.3f ms\n"
        "  Parse Time: %.3f ms\n"
        "\n"
        "Memory:\n"
        "  Peak Usage: %.2f MB\n"
        "  Current Usage: %.2f MB\n"
        "  Allocations: %u\n"
        "  Deallocations: %u\n"
        "  Allocation Efficiency: %.1f%%\n"
        "\n"
        "Cache:\n"
        "  Cache Hits: %u\n"
        "  Cache Misses: %u\n"
        "  Hit Rate: %.1f%%\n"
        "\n"
        "Performance:\n"
        "  Total Cache Accesses: %u\n"
        "  Memory Efficiency: %.1f%%\n",
        
        metrics->execution_time_ns / 1000000.0,
        metrics->parse_time_ns / 1000000.0,
        
        metrics->memory_peak_bytes / (1024.0 * 1024.0),
        metrics->memory_current_bytes / (1024.0 * 1024.0),
        metrics->allocations,
        metrics->deallocations,
        alloc_efficiency,
        
        metrics->cache_hits,
        metrics->cache_misses,
        cache_hit_rate,
        
        total_cache_accesses,
        cache_hit_rate
    );
    
    return report;
}