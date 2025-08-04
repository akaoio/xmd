/**
 * @file get_current_timestamp_ms.c
 * @brief Get current timestamp in milliseconds
 * 
 * This file contains ONLY the get_current_timestamp_ms function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast/evaluator/builtin/ast_evaluate_date/ast_evaluate_date.c
 */

#include <time.h>
#include "utils/common/common_macros.h"
#include "date_functions.h"

/**
 * @brief Get current timestamp in milliseconds
 * @return Current timestamp or 0 on error
 */
double get_current_timestamp_ms(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        return (double)(ts.tv_sec * 1000) + (double)(ts.tv_nsec / 1000000);
    }
    return (double)time(NULL) * 1000.0; // Fallback to seconds precision
}