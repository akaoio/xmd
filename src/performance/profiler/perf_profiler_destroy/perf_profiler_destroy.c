/**
 * @file perf_profiler_destroy.c
 * @brief Destroy performance profiler
 */

#include <stdlib.h>
#include "../../../../include/performance_internal.h"
void perf_profiler_destroy(perf_profiler* profiler) {
    if (!profiler) return;
    free(profiler->profile_data);
    free(profiler);
}
