#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file benchmark_run.c
 * @brief Benchmark execution function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../../include/performance.h"

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