/**
 * @file resize_results_if_needed.c
 * @brief Benchmark results array resizing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/performance.h"

/**
 * @brief Resize results array if needed
 * @param suite Benchmark suite
 * @return 0 on success, -1 on error
 */
int resize_results_if_needed(benchmark_suite* suite) {
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