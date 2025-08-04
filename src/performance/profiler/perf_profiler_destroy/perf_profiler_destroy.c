/**
 * @file perf_profiler_destroy.c
 * @brief Destroy performance profiler
 */

#include <stdlib.h>
#include "../../../../include/performance_internal.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"
void perf_profiler_destroy(perf_profiler* profiler) {
    XMD_VALIDATE_PTR_RETURN_VOID(profiler);
    XMD_FREE_SAFE(profiler->profile_data);
    XMD_FREE_SAFE(profiler);
}
