/**
 * @file get_elapsed_time_ms.c
 * @brief Elapsed time calculation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include "../../../include/platform.h"

/**
 * @brief Get elapsed time in milliseconds
 * @param start_time Start time
 * @return Elapsed time in milliseconds
 */
long get_elapsed_time_ms(const xmd_time_t* start_time) {
    xmd_time_t current_time;
    xmd_get_time(&current_time);
    
    long elapsed_sec = current_time.seconds - start_time->seconds;
    long elapsed_nsec = current_time.nanoseconds - start_time->nanoseconds;
    
    return (elapsed_sec * 1000) + (elapsed_nsec / 1000000);
}