/**
 * @file date_functions.h
 * @brief Header for date utility functions
 * 
 * This header declares date utility functions that have been
 * separated following the Genesis principle (one function per file).
 */

#ifndef DATE_FUNCTIONS_H
#define DATE_FUNCTIONS_H

/**
 * @brief Get current timestamp in milliseconds
 * @return Current timestamp or 0 on error
 */
double get_current_timestamp_ms(void);

/**
 * @brief Parse date string (simple YYYY-MM-DD format)
 * @param date_str Date string to parse
 * @return Timestamp in milliseconds or 0 on error
 */
double parse_date_string(const char* date_str);

/**
 * @brief Calculate date difference
 * @param timestamp1 First timestamp in milliseconds
 * @param timestamp2 Second timestamp in milliseconds
 * @param unit Unit for difference ("years", "months", "days", "hours", "minutes", "seconds")
 * @return Difference in specified unit
 */
double calculate_date_diff(double timestamp1, double timestamp2, const char* unit);

#endif // DATE_FUNCTIONS_H