/**
 * @file benchmark_generate_report.c
 * @brief Generate benchmark report
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Generate benchmark report
 * @param suite Benchmark suite
 * @return Allocated report string or NULL on error
 */
char* benchmark_generate_report(benchmark_suite* suite) {
    if (!suite) {
        return NULL;
    }
    
    size_t report_size = 4096;
    char* report;
    XMD_MALLOC_DYNAMIC(report, report_size, NULL);
    
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
