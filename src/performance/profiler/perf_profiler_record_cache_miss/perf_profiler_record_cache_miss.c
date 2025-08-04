/**
 * @file perf_profiler_record_cache_miss.c
 * @brief Record cache miss
 */

#include "../../../../include/performance_internal.h"
#include "utils/common/validation_macros.h"
void perf_profiler_record_cache_miss(perf_profiler* profiler) {
    XMD_VALIDATE_PTR_RETURN_VOID(profiler);
    profiler->metrics.cache_misses++;
}
