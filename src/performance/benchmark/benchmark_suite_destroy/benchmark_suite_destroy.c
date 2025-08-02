/**
 * @file benchmark_suite_destroy.c
 * @brief Destroy benchmark suite
 */

#include <stdlib.h>
#include "../../../../include/performance_internal.h"
void benchmark_suite_destroy(benchmark_suite* suite) {
    if (!suite) {
        return;
    }
    free(suite->suite_name);
    free(suite->results);
    free(suite);
}
