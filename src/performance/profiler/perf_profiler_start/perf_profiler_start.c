/**
 * @file perf_profiler_start.c
 * @brief Start profiling session
 */

#include "../../../../include/performance_internal.h"
#include "../../../../include/platform.h"
#include "utils/common/validation_macros.h"

/**
 * @brief FUNCTION_Start profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_start(perf_profiler* profiler) {
    XMD_VALIDATE_PTR_RETURN(profiler, -1);
    xmd_get_time(&profiler->start_time);
    profiler->is_active = true;
    return 0;
}
