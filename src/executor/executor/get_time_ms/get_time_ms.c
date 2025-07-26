/**
 * @file get_time_ms.c
 * @brief Get current time in milliseconds
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Get current time in milliseconds
 * @return Current time in milliseconds
 */
long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}