/**
 * @file string_duplicate.c
 * @brief Implementation of safe string duplication utility
 * 
 * Provides a safe wrapper around string duplication with proper
 * null checking and memory allocation.
 */

#include <stdlib.h>
#include <string.h>
#include "string_duplicate.h"

/**
 * @brief Duplicate a string safely
 * 
 * Creates a new copy of the input string with proper null termination.
 * The caller is responsible for freeing the returned memory.
 * 
 * @param str The string to duplicate
 * @return New string copy on success, NULL if str is NULL or allocation fails
 */
char* string_duplicate(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t length = strlen(str);
    char* copy = malloc(length + 1);
    
    if (copy == NULL) {
        return NULL;
    }
    
    strcpy(copy, str);
    return copy;
}