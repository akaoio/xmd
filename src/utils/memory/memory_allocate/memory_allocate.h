/**
 * @file memory_allocate.h
 * @brief Safe memory allocation wrapper
 * 
 * Provides a wrapper around malloc with consistent error handling.
 */

#ifndef MEMORY_ALLOCATE_H
#define MEMORY_ALLOCATE_H

#include <stddef.h>

/**
 * @brief Allocate memory safely
 * 
 * Allocates memory of the specified size with proper error handling.
 * Returns NULL for zero-size allocations.
 * 
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory on success, NULL on failure or if size is 0
 */
void* memory_allocate(size_t size);

#endif /* MEMORY_ALLOCATE_H */