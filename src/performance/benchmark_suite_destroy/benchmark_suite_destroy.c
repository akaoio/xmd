/**
 * @file benchmark_suite_destroy.c
 * @brief Benchmark suite cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/performance.h"

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