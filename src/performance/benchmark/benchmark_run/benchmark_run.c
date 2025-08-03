/**
 * @file benchmark_run.c
 * @brief Run performance benchmark
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

uint64_t get_time_ns(void);
void calculate_stats(uint64_t* times, uint32_t count, benchmark_result* result);

/**
 * @brief Run performance benchmark
 * @param suite Benchmark suite
 * @param test_name Name of the test
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
    
    XMD_FREE_SAFE(times);
    return 0;
}
