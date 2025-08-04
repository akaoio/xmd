/**
 * @file benchmark_suite_destroy.c
 * @brief Destroy benchmark suite
 */

#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "utils/common/common_macros.h"
void benchmark_suite_destroy(benchmark_suite* suite) {
    if (!suite) {
        return;
    }
    XMD_FREE_SAFE(suite->suite_name);
    XMD_FREE_SAFE(suite->results);
    XMD_FREE_SAFE(suite);
}
