/**
 * @file profiler.c
 * @brief Performance profiling system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/platform.h"
#include "../../../include/performance.h"

/**
 * @brief Get current time in nanoseconds
 * @return Time in nanoseconds
 */
static uint64_t get_time_ns(void) {
    xmd_time_t time;
    if (xmd_get_time(&time) != 0) {
        return 0;
    }
    return (uint64_t)time.seconds * 1000000000ULL + (uint64_t)time.nanoseconds;
}

/**
 * @brief Calculate time difference in nanoseconds
 * @param start Start time
 * @param end End time
 * @return Difference in nanoseconds
 */
static uint64_t time_diff_ns(const xmd_time_t* start, const xmd_time_t* end) {
    uint64_t start_ns = (uint64_t)start->seconds * 1000000000ULL + (uint64_t)start->nanoseconds;
    uint64_t end_ns = (uint64_t)end->seconds * 1000000000ULL + (uint64_t)end->nanoseconds;
    return end_ns - start_ns;
}

/**
 * @brief Get current memory usage using platform-specific method
 * @return Memory usage in bytes or 0 if unavailable
 */
static uint64_t get_memory_usage(void) {
    uint64_t mem = xmd_get_memory_usage();
    return mem;
}

/**
 * @brief Initialize performance profiler
 * @return Profiler instance or NULL on error
 */
perf_profiler* perf_profiler_create(void) {
    perf_profiler* profiler = calloc(1, sizeof(perf_profiler));
    if (!profiler) {
        return NULL;
    }
    
    // Initialize metrics
    memset(&profiler->metrics, 0, sizeof(perf_metrics));
    profiler->is_active = false;
    profiler->profile_data = NULL;
    profiler->profile_size = 0;
    
    return profiler;
}

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

/**
 * @brief Record cache hit
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_hit(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.cache_hits++;
}

/**
 * @brief Record cache miss
 * @param profiler Profiler instance
 */
void perf_profiler_record_cache_miss(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.cache_misses++;
}

/**
 * @brief Get current metrics
 * @param profiler Profiler instance
 * @return Pointer to metrics or NULL on error
 */
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler) {
    if (!profiler) {
        return NULL;
    }
    
    return &profiler->metrics;
}

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

/**
 * @brief Destroy profiler instance
 * @param profiler Profiler instance
 */
void perf_profiler_destroy(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    free(profiler->profile_data);
    free(profiler);
}