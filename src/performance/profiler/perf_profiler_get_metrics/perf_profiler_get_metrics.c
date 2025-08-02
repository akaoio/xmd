/**
 * @file perf_profiler_get_metrics.c
 * @brief Get current metrics
 */

#include "../../../../include/performance_internal.h"

/**
 * @brief Function implementation
 */
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler) {
    if (!profiler) return NULL;
    return &profiler->metrics;
}
