/**
 * @file string_duplicate.h
 * @brief Safe string duplication utility
 * 
 * Provides a safe wrapper around string duplication with proper
 * null checking and memory allocation.
 */

#ifndef STRING_DUPLICATE_H
#define STRING_DUPLICATE_H

/**
 * @brief Duplicate a string safely
 * 
 * Creates a new copy of the input string with proper null termination.
 * The caller is responsible for freeing the returned memory.
 * 
 * @param str The string to duplicate
 * @return New string copy on success, NULL if str is NULL or allocation fails
 */
char* string_duplicate(const char* str);

#endif /* STRING_DUPLICATE_H */