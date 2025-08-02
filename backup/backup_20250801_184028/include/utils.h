/**
 * @file utils.h
 * @brief Common utility functions
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef XMD_UTILS_H
#define XMD_UTILS_H

#include <stddef.h>
#include "variable.h"

/**
 * @brief Calculate hash for a string key using djb2 algorithm
 * @param key String key to hash
 * @param capacity Capacity of hash table (for modulo)
 * @return Hash value
 */
size_t xmd_hash_key(const char* key, size_t capacity);

/**
 * @brief Convert variable to number (double)
 * @param var Variable to convert
 * @return Numeric value or 0.0 if conversion fails
 */
double xmd_variable_to_number(const variable* var);

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if equal, false otherwise
 */
bool xmd_variable_equals(const variable* a, const variable* b);

/**
 * @brief Safe malloc with NULL check
 * @param size Size to allocate
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc(size_t size);

/**
 * @brief Allocate memory safely
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory on success, NULL on failure or if size is 0
 */
void* memory_allocate(size_t size);

/**
 * @brief Free memory safely and set pointer to NULL
 * @param ptr Pointer to pointer to memory to free
 */
void memory_free_safe(void** ptr);


/**
 * @brief Extract a substring from a string
 * @param str Source string
 * @param start Starting position
 * @param length Length of substring
 * @return Extracted substring or NULL on failure
 */
char* string_extract(const char* str, size_t start, size_t length);

/**
 * @brief Safe calloc with NULL check
 * @param count Number of elements
 * @param size Size of each element
 * @return Allocated and zeroed memory or NULL on failure
 */
void* xmd_calloc(size_t count, size_t size);

/**
 * @brief Safe realloc with NULL check
 * @param ptr Existing pointer
 * @param size New size
 * @return Reallocated memory or NULL on failure
 */
void* xmd_realloc(void* ptr, size_t size);

/**
 * @brief Safe string duplication
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* xmd_strdup(const char* str);

/**
 * @brief Expand array capacity safely
 * @param ptr Pointer to array pointer
 * @param current_capacity Current capacity
 * @param element_size Size of each element
 * @return New capacity or 0 on failure
 */
size_t xmd_expand_array(void** ptr, size_t current_capacity, size_t element_size);

/**
 * @brief Check if pointer is NULL and handle error
 * @param ptr Pointer to check
 * @param error_msg Error message if NULL
 * @return true if NULL (error), false if valid
 */
bool xmd_check_null(const void* ptr, const char* error_msg);

/**
 * @brief Safe memory allocation with error logging
 * @param size Size to allocate
 * @param error_msg Error message context
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc_safe(size_t size, const char* error_msg);

/**
 * @brief Macro for NULL pointer checks with return
 */
#define XMD_NULL_CHECK_RETURN(ptr, retval) \
    do { if (!(ptr)) return (retval); } while(0)

/**
 * @brief Macro for NULL pointer checks with goto
 */
#define XMD_NULL_CHECK_GOTO(ptr, label) \
    do { if (!(ptr)) goto label; } while(0)

/**
 * @brief Macro for memory allocation with NULL check
 */
#define XMD_MALLOC_CHECK(ptr, size, retval) \
    do { \
        (ptr) = xmd_malloc(size); \
        if (!(ptr)) return (retval); \
    } while(0)

/**
 * @brief Process escape sequences in string literals
 * @param input Input string with potential escape sequences
 * @return New string with processed escape sequences (caller must free) or NULL on error
 */
char* process_escape_sequences(const char* input);

#endif /* XMD_UTILS_H */
