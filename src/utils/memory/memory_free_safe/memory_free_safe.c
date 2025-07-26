/**
 * @file memory_free_safe.c
 * @brief Implementation of safe memory deallocation wrapper
 * 
 * Provides a safe wrapper around free that prevents double-free errors.
 */

#include <stdlib.h>
#include "memory_free_safe.h"

/**
 * @brief Free memory safely and set pointer to NULL
 * 
 * Frees the memory pointed to by *ptr and sets *ptr to NULL.
 * This prevents double-free errors and use-after-free bugs.
 * Handles NULL pointers gracefully.
 * 
 * @param ptr Pointer to the pointer to free (can be NULL)
 */
void memory_free_safe(void** ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }
    
    free(*ptr);
    *ptr = NULL;
}
