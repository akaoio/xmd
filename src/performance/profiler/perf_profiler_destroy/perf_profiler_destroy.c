/**
 * @file perf_profiler_destroy.c
 * @brief Destroy performance profiler
 */

#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "../../../utils/common/common_macros.h"
void perf_profiler_destroy(perf_profiler* profiler) {
    if (!profiler) return;
    XMD_FREE_SAFE(profiler->profile_data);
    XMD_FREE_SAFE(profiler);
}
