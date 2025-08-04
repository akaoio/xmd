/**
 * @file perf_profiler_create.c
 * @brief Create performance profiler
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/performance.h"
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"
perf_profiler* perf_profiler_create(void) {
    XMD_CREATE_VALIDATED(profiler, perf_profiler, sizeof(perf_profiler), NULL);
    memset(profiler, 0, sizeof(perf_profiler));
    profiler->is_active = false;
    return profiler;
}
