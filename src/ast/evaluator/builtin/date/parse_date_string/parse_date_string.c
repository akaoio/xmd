/**
 * @file parse_date_string.c
 * @brief Parse date string (simple YYYY-MM-DD format)
 * 
 * This file contains ONLY the parse_date_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast/evaluator/builtin/ast_evaluate_date/ast_evaluate_date.c
 */

#include <time.h>
#include <stdio.h>
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
#include "date_functions.h"

/**
 * @brief Parse date string (simple YYYY-MM-DD format)
 * @param date_str Date string to parse
 * @return Timestamp in milliseconds or 0 on error
 */
double parse_date_string(const char* date_str) {
    XMD_VALIDATE_PTR_RETURN(date_str, 0.0);
    
    struct tm tm = {0};
    if (sscanf(date_str, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) == 3) {
        tm.tm_year -= 1900; // Years since 1900
        tm.tm_mon -= 1;     // Months 0-11
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;
        
        time_t t = mktime(&tm);
        if (t != -1) {
            return (double)t * 1000.0; // Convert to milliseconds
        }
    }
    
    return 0.0;
}