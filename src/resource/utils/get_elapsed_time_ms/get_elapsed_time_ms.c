/**
 * @file get_elapsed_time_ms.c
 * @brief Get elapsed time in milliseconds
 */

#include <stdint.h>
#include "../../../../include/platform.h"
#include "../../../../utils/common/common_macros.h"
long get_elapsed_time_ms(const xmd_time_t* start_time) {
    XMD_VALIDATE_PTRS(0, start_time);
    xmd_time_t current;
    xmd_get_time(&current);
    int64_t diff_seconds = current.seconds - start_time->seconds;
    int64_t diff_nanoseconds = current.nanoseconds - start_time->nanoseconds;
    return (long)(diff_seconds * 1000 + diff_nanoseconds / 1000000);
}
