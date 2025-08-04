/**
 * @file calculate_date_diff.c
 * @brief Calculate date difference
 * 
 * This file contains ONLY the calculate_date_diff function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast/evaluator/builtin/ast_evaluate_date/ast_evaluate_date.c
 */

#include <string.h>
#include "utils/common/common_macros.h"
#include "date_functions.h"

/**
 * @brief Calculate date difference
 * @param timestamp1 First timestamp in milliseconds
 * @param timestamp2 Second timestamp in milliseconds
 * @param unit Unit for difference ("years", "months", "days", "hours", "minutes", "seconds")
 * @return Difference in specified unit
 */
double calculate_date_diff(double timestamp1, double timestamp2, const char* unit) {
    double diff_ms = timestamp1 - timestamp2;
    double diff_seconds = diff_ms / 1000.0;
    
    if (STR_EQUALS(unit, "seconds")) {
        return diff_seconds;
    } else if (STR_EQUALS(unit, "minutes")) {
        return diff_seconds / 60.0;
    } else if (STR_EQUALS(unit, "hours")) {
        return diff_seconds / 3600.0;
    } else if (STR_EQUALS(unit, "days")) {
        return diff_seconds / 86400.0;
    } else if (STR_EQUALS(unit, "months")) {
        return diff_seconds / (86400.0 * 30.44); // Average month
    } else if (STR_EQUALS(unit, "years")) {
        return diff_seconds / (86400.0 * 365.25); // Average year with leap years
    }
    
    return diff_seconds; // Default to seconds
}