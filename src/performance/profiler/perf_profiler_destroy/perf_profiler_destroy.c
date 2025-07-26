/**
 * @file perf_profiler_destroy.c
 * @brief Destroy profiler instance
 * @author XMD Team
 */

#include "../../../../include/profiler_internal.h"

/**
 * @brief Destroy profiler instance
 * @param profiler Profiler instance
 */
void perf_profiler_destroy(perf_profiler* profiler) {
    if (!profiler) {
        return;
    }
    
    free(profiler->profile_data);
    free(profiler);
}