/**
 * @file benchmark.c
 * @brief Benchmark suite for performance testing
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../../../include/performance.h"

/**
 * @brief Get current time in nanoseconds
 * @return Time in nanoseconds
 */
static uint64_t get_time_ns(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

/**
 * @brief Compare function for sorting benchmark times
 * @param a First time value
 * @param b Second time value
 * @return Comparison result
 */
static int compare_times(const void* a, const void* b) {
    uint64_t time_a = *(const uint64_t*)a;
    uint64_t time_b = *(const uint64_t*)b;
    
    if (time_a < time_b) return -1;
    if (time_a > time_b) return 1;
    return 0;
}

/**
 * @brief Calculate statistics from timing data
 * @param times Array of timing measurements
 * @param count Number of measurements
 * @param result Result structure to populate
 */
static void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result) {
    if (!times || count == 0 || !result) {
        return;
    }
    
    // Sort times for median calculation
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
    
    // Calculate throughput (operations per second)
    if (result->avg_time_ns > 0) {
        result->throughput_ops_per_sec = 1000000000.0 / result->avg_time_ns;
    } else {
        result->throughput_ops_per_sec = 0.0;
    }
    
    result->iterations = count;
}

/**
 * @brief Create benchmark suite
 * @param name Suite name
 * @return Suite instance or NULL on error
 */
benchmark_suite* benchmark_suite_create(const char* name) {
    if (!name) {
        return NULL;
    }
    
    benchmark_suite* suite = calloc(1, sizeof(benchmark_suite));
    if (!suite) {
        return NULL;
    }
    
    suite->suite_name = strdup(name);
    if (!suite->suite_name) {
        free(suite);
        return NULL;
    }
    
    suite->result_capacity = 16; // Initial capacity
    suite->results = calloc(suite->result_capacity, sizeof(benchmark_result));
    if (!suite->results) {
        free(suite->suite_name);
        free(suite);
        return NULL;
    }
    
    suite->result_count = 0;
    
    return suite;
}

/**
 * @brief Resize results array if needed
 * @param suite Benchmark suite
 * @return 0 on success, -1 on error
 */
static int resize_results_if_needed(benchmark_suite* suite) {
    if (!suite) {
        return -1;
    }
    
    if (suite->result_count >= suite->result_capacity) {
        size_t new_capacity = suite->result_capacity * 2;
        benchmark_result* new_results = realloc(suite->results, 
                                               new_capacity * sizeof(benchmark_result));
        if (!new_results) {
            return -1;
        }
        
        suite->results = new_results;
        suite->result_capacity = new_capacity;
        
        // Zero out new entries
        memset(&suite->results[suite->result_count], 0, 
               (new_capacity - suite->result_capacity) * sizeof(benchmark_result));
    }
    
    return 0;
}

/**
 * @brief Run benchmark function
 * @param suite Benchmark suite
 * @param test_name Test name
 * @param test_func Function to benchmark
 * @param test_data Data to pass to function
 * @param iterations Number of iterations
 * @return 0 on success, -1 on error
 */
int benchmark_run(benchmark_suite* suite, const char* test_name,
                  int (*test_func)(void*), void* test_data, uint32_t iterations) {
    if (!suite || !test_name || !test_func || iterations == 0) {
        return -1;
    }
    
    if (resize_results_if_needed(suite) != 0) {
        return -1;
    }
    
    // Allocate timing array
    uint64_t* times = malloc(iterations * sizeof(uint64_t));
    if (!times) {
        return -1;
    }
    
    // Warm up run (not timed)
    test_func(test_data);
    
    // Run benchmark iterations
    for (uint32_t i = 0; i < iterations; i++) {
        uint64_t start_time = get_time_ns();
        
        int result = test_func(test_data);
        
        uint64_t end_time = get_time_ns();
        
        if (result != 0) {
            // Test function failed
            free(times);
            return -1;
        }
        
        times[i] = end_time - start_time;
    }
    
    // Create result entry
    benchmark_result* result = &suite->results[suite->result_count];
    result->test_name = strdup(test_name);
    if (!result->test_name) {
        free(times);
        return -1;
    }
    
    // Calculate statistics
    calculate_stats(times, iterations, result);
    
    free(times);
    suite->result_count++;
    
    return 0;
}

/**
 * @brief Generate benchmark report
 * @param suite Benchmark suite
 * @return Report string (must be freed) or NULL on error
 */
char* benchmark_generate_report(benchmark_suite* suite) {
    if (!suite || suite->result_count == 0) {
        return NULL;
    }
    
    // Calculate required buffer size
    size_t buffer_size = 1024; // Header
    buffer_size += suite->result_count * 512; // Per test
    
    char* report = malloc(buffer_size);
    if (!report) {
        return NULL;
    }
    
    // Generate header
    int pos = snprintf(report, buffer_size,
        "=== Benchmark Report: %s ===\n"
        "\n"
        "%-20s %10s %10s %10s %10s %8s %12s\n"
        "%-20s %10s %10s %10s %10s %8s %12s\n",
        suite->suite_name,
        "Test Name", "Min (ns)", "Max (ns)", "Avg (ns)", "Med (ns)", "Iters", "Ops/sec",
        "--------------------", "----------", "----------", "----------", "----------", "--------", "------------"
    );
    
    // Generate results
    for (size_t i = 0; i < suite->result_count && pos < buffer_size - 512; i++) {
        const benchmark_result* result = &suite->results[i];
        
        pos += snprintf(report + pos, buffer_size - pos,
            "%-20s %10lu %10lu %10lu %10lu %8u %12.1f\n",
            result->test_name ? result->test_name : "Unknown",
            result->min_time_ns,
            result->max_time_ns,
            result->avg_time_ns,
            result->median_time_ns,
            result->iterations,
            result->throughput_ops_per_sec
        );
    }
    
    // Add summary statistics
    if (pos < buffer_size - 256) {
        uint64_t total_min = UINT64_MAX;
        uint64_t total_max = 0;
        uint64_t total_avg = 0;
        double total_throughput = 0.0;
        
        for (size_t i = 0; i < suite->result_count; i++) {
            const benchmark_result* result = &suite->results[i];
            if (result->min_time_ns < total_min) {
                total_min = result->min_time_ns;
            }
            if (result->max_time_ns > total_max) {
                total_max = result->max_time_ns;
            }
            total_avg += result->avg_time_ns;
            total_throughput += result->throughput_ops_per_sec;
        }
        
        if (suite->result_count > 0) {
            total_avg /= suite->result_count;
        }
        
        pos += snprintf(report + pos, buffer_size - pos,
            "\n"
            "Summary:\n"
            "  Total Tests: %zu\n"
            "  Fastest: %lu ns\n"
            "  Slowest: %lu ns\n"
            "  Average: %lu ns\n"
            "  Total Throughput: %.1f ops/sec\n",
            suite->result_count,
            total_min,
            total_max,
            total_avg,
            total_throughput
        );
    }
    
    return report;
}

/**
 * @brief Destroy benchmark suite
 * @param suite Benchmark suite
 */
void benchmark_suite_destroy(benchmark_suite* suite) {
    if (!suite) {
        return;
    }
    
    // Free all result test names
    for (size_t i = 0; i < suite->result_count; i++) {
        free(suite->results[i].test_name);
    }
    
    free(suite->results);
    free(suite->suite_name);
    free(suite);
}