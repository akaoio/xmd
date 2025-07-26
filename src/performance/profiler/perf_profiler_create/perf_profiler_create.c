/**
 * @file perf_profiler_create.c
 * @brief Performance profiler creation function
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Initialize performance profiler
 * @return Profiler instance or NULL on error
 */
perf_profiler* perf_profiler_create(void) {
    perf_profiler* profiler = calloc(1, sizeof(perf_profiler));
    if (!profiler) {
        return NULL;
    }
    
    // Initialize metrics
    memset(&profiler->metrics, 0, sizeof(perf_metrics));
    profiler->is_active = false;
    profiler->profile_data = NULL;
    profiler->profile_size = 0;
    
    return profiler;
}