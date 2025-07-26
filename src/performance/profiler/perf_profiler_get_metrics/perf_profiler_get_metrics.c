/**
 * @file perf_profiler_get_metrics.c
 * @brief Get profiler metrics
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Get current metrics
 * @param profiler Profiler instance
 * @return Pointer to metrics or NULL on error
 */
const perf_metrics* perf_profiler_get_metrics(perf_profiler* profiler) {
    if (!profiler) {
        return NULL;
    }
    
    return &profiler->metrics;
}