/**
 * @file perf_profiler_get_metrics.c
 * @brief Get current metrics
 */

#include "../../../../include/performance_internal.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Function implementation
 */
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler) {
    XMD_VALIDATE_PTR_RETURN(profiler, NULL);
    return &profiler->metrics;
}
