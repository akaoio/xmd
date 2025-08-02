/**
 * @file performance.c
 * @brief Consolidated performance monitoring for XMD
 * @author XMD Development Team
 *
 * All performance benchmarking, profiling, and optimization functionality
 * consolidated from 32 separate directories.
 */

#include "../include/performance_internal.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Get current time in nanoseconds
 * @return Current time in nanoseconds
 */
uint64_t get_time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

// ============================================================================
// BENCHMARK SYSTEM
// ============================================================================

/**
 * @brief Run performance benchmark
 * @param suite Benchmark suite
 * @param test_name Test name
 * @param test_func Function to benchmark
 * @param test_data Data to pass to function
 * @param iterations Number of iterations
 * @return 0 on success, -1 on error
 */
int benchmark_run(benchmark_suite* suite, const char* test_name,
                  int (*test_func)(void*), void* test_data, uint32_t iterations) {
    if (!suite || !test_name || !test_func) {
        return -1;
    }
    
    // Ensure capacity
    if (suite->result_count >= suite->result_capacity) {
        size_t new_capacity = suite->result_capacity * 2;
        benchmark_result* new_results = xmd_realloc(suite->results, new_capacity * sizeof(benchmark_result));
        if (!new_results) {
            return -1;
        }
        suite->results = new_results;
        suite->result_capacity = new_capacity;
    }
    
    // Run benchmark
    uint64_t* times = xmd_malloc(iterations * sizeof(uint64_t));
    if (!times) {
        return -1;
    }
    
    for (uint32_t i = 0; i < iterations; i++) {
        uint64_t start = get_time_ns();
        test_func(test_data);
        uint64_t end = get_time_ns();
        times[i] = end - start;
    }
    
    // Store result
    benchmark_result* result = &suite->results[suite->result_count++];
    result->test_name = xmd_strdup(test_name);
    result->iterations = iterations;
    calculate_stats(times, iterations, result);
    
    free(times);
    return 0;
}

/**
 * @brief Generate benchmark report
 * @param suite Benchmark suite
 * @return Report string (must be freed)
 */
char* benchmark_generate_report(benchmark_suite* suite) {
    if (!suite) {
        return NULL;
    }
    
    size_t report_size = 4096;
    char* report = xmd_malloc(report_size);
    if (!report) {
        return NULL;
    }
    
    snprintf(report, report_size, 
        "Benchmark Report: %s\n"
        "Total Time: %lu ns\n"
        "Tests Run: %zu\n\n",
        suite->suite_name ? suite->suite_name : "Unnamed", 
        0UL, // Total time placeholder
        suite->result_count);
    
    for (size_t i = 0; i < suite->result_count; i++) {
        const benchmark_result* result = &suite->results[i];
        char test_line[256];
        
        snprintf(test_line, sizeof(test_line),
            "Test %zu: %lu ns\n",
            i + 1, result->avg_time_ns);
            
        strncat(report, test_line, report_size - strlen(report) - 1);
    }
    
    return report;
}

/**
 * @brief Destroy benchmark suite
 * @param suite Benchmark suite to destroy
 */
void benchmark_suite_destroy(benchmark_suite* suite) {
    if (!suite) {
        return;
    }
    
    free(suite->suite_name);
    free(suite->results);
    free(suite);
}

// ============================================================================
// PERFORMANCE PROFILER
// ============================================================================

/**
 * @brief Create performance profiler
 * @return New profiler or NULL on error
 */
perf_profiler* perf_profiler_create(void) {
    perf_profiler* profiler = xmd_malloc(sizeof(perf_profiler));
    if (!profiler) {
        return NULL;
    }
    
    memset(profiler, 0, sizeof(perf_profiler));
    profiler->is_active = false;
    
    return profiler;
}

/**
 * @brief Start profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_start(perf_profiler* profiler) {
    if (!profiler) {
        return -1;
    }
    
    xmd_get_time(&profiler->start_time);
    profiler->is_active = true;
    
    return 0;
}

/**
 * @brief Stop profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_stop(perf_profiler* profiler) {
    if (!profiler || !profiler->is_active) {
        return -1;
    }
    
    xmd_get_time(&profiler->end_time);
    profiler->is_active = false;
    
    return 0;
}

/**
 * @brief Record memory allocation
 * @param profiler Performance profiler
 * @param size Allocation size
 */
void perf_profiler_record_alloc(perf_profiler* profiler, size_t size) {
    if (!profiler) {
        return;
    }
    
    profiler->metrics.allocations++;
    profiler->metrics.memory_current_bytes += size;
    if (profiler->metrics.memory_current_bytes > profiler->metrics.memory_peak_bytes) {
        profiler->metrics.memory_peak_bytes = profiler->metrics.memory_current_bytes;
    }
}

/**
 * @brief Record memory deallocation
 * @param profiler Performance profiler
 * @param size Deallocation size
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
 * @brief Generate profiler report
 * @param profiler Performance profiler
 * @return Report string (must be freed)
 */
char* perf_profiler_generate_report(perf_profiler* profiler) {
    if (!profiler) {
        return NULL;
    }
    
    char* report = xmd_malloc(2048);
    if (!report) {
        return NULL;
    }
    
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

/**
 * @brief Destroy performance profiler
 * @param profiler Profiler to destroy
 */
void perf_profiler_destroy(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    free(profiler->profile_data);
    free(profiler);
}

// ============================================================================
// OPTIMIZATION UTILITIES
// ============================================================================


/**
 * @brief Calculate statistics from timing data
 * @param times Array of timing measurements
 * @param count Number of measurements
 * @param result Benchmark result to populate
 */
void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result) {
    if (!times || !count || !result) {
        return;
    }
    
    // Sort times
    qsort(times, count, sizeof(uint64_t), compare_times);
    
    // Calculate min, max, median
    result->min_time_ns = times[0];
    result->max_time_ns = times[count - 1];
    result->median_time_ns = times[count / 2];
    
    // Calculate average
    uint64_t total = 0;
    for (uint32_t i = 0; i < count; i++) {
        total += times[i];
    }
    result->avg_time_ns = total / count;
    
    // Calculate throughput
    if (result->avg_time_ns > 0) {
        result->throughput_ops_per_sec = 1000000000.0 / result->avg_time_ns;
    }
}

/**
 * @brief Compare function for sorting times
 * @param a First time value
 * @param b Second time value
 * @return Comparison result
 */
int compare_times(const void* a, const void* b) {
    uint64_t time1 = *(const uint64_t*)a;
    uint64_t time2 = *(const uint64_t*)b;
    if (time1 < time2) return -1;
    if (time1 > time2) return 1;
    return 0;
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
