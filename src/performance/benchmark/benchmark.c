#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file benchmark.c
 * @brief Benchmark suite creation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/performance.h"

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
