/**
 * @file benchmark_generate_report.c
 * @brief Benchmark report generation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../../include/performance.h"

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