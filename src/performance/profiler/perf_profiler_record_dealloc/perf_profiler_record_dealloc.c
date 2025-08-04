/**
 * @file perf_profiler_record_dealloc.c
 * @brief Record memory deallocation
 */

#include <stddef.h>
#include "../../../../include/performance_internal.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Function implementation
 */
void perf_profiler_record_dealloc(perf_profiler* profiler, size_t size) {
    XMD_VALIDATE_PTR_RETURN_VOID(profiler);
    profiler->metrics.deallocations++;
    if (profiler->metrics.memory_current_bytes >= size) {
        profiler->metrics.memory_current_bytes -= size;
    }
}
