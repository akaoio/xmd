/**
 * @file memory_free_safe.h
 * @brief Safe memory deallocation wrapper
 * 
 * Provides a safe wrapper around free that prevents double-free errors.
 */

#ifndef MEMORY_FREE_SAFE_H
#define MEMORY_FREE_SAFE_H

/**
 * @brief Free memory safely and set pointer to NULL
 * 
 * Frees the memory pointed to by *ptr and sets *ptr to NULL.
 * This prevents double-free errors and use-after-free bugs.
 * 
 * @param ptr Pointer to the pointer to free (can be NULL)
 */
void memory_free_safe(void** ptr);

#endif /* MEMORY_FREE_SAFE_H */