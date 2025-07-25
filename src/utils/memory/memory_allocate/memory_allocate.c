/**
 * @file memory_allocate.c
 * @brief Implementation of safe memory allocation wrapper
 * 
 * Provides a wrapper around malloc with consistent error handling.
 */

#include <stdlib.h>
#include "memory_allocate.h"

/**
 * @brief Allocate memory safely
 * 
 * Allocates memory of the specified size with proper error handling.
 * Returns NULL for zero-size allocations to maintain consistent behavior.
 * 
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory on success, NULL on failure or if size is 0
 */
void* memory_allocate(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    return malloc(size);
}