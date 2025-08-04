/**
 * @file perf_profiler_record_cache_hit.c
 * @brief Record cache hit
 */

#include "../../../../include/performance_internal.h"
#include "utils/common/validation_macros.h"
void perf_profiler_record_cache_hit(perf_profiler* profiler) {
    XMD_VALIDATE_PTR_RETURN_VOID(profiler);
    profiler->metrics.cache_hits++;
}
