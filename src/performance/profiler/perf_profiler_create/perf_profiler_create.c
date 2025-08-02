/**
 * @file perf_profiler_create.c
 * @brief Create performance profiler
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/performance.h"
#include "../../../../include/utils.h"
perf_profiler* perf_profiler_create(void) {
    perf_profiler* profiler = xmd_malloc(sizeof(perf_profiler));
    if (!profiler) {
        return NULL;
    }
    memset(profiler, 0, sizeof(perf_profiler));
    profiler->is_active = false;
    return profiler;
}
