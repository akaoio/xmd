/**
 * @file utils_consolidated.c
 * @brief Consolidated utility functions for XMD
 * @author XMD Development Team
 * @date 2025-07-31
 * 
 * This file consolidates all utility functionality from utils/ directory:
 * - memory.c: Memory management functions
 * - misc.c: Hash functions and miscellaneous utilities  
 * - string.c: String manipulation utilities
 * 
 * Moved to src level to eliminate utils/ directory toward 20-directory goal.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/utils_internal.h"

// ============================================================================
// MEMORY MANAGEMENT (from memory.c)
// ============================================================================

/**
 * @brief Safe malloc with NULL check
 * @param size Size to allocate
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    return malloc(size);
}

/**
 * @brief Safe calloc wrapper
 * @param count Number of elements
 * @param size Size of each element
 * @return Allocated zeroed memory or NULL on failure
 */
void* xmd_calloc(size_t count, size_t size) {
    if (count == 0 || size == 0) {
        return NULL;
    }
    return calloc(count, size);
}

/**
 * @brief Safe realloc wrapper
 * @param ptr Pointer to reallocate
 * @param size New size
 * @return Reallocated memory or NULL on failure
 */
void* xmd_realloc(void* ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    return realloc(ptr, size);
}

/**
 * @brief Safe free wrapper
 * @param ptr Pointer to free
 */
void xmd_free(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

/**
 * @brief Safe memory allocation with error checking
 * @param size Size to allocate
 * @return Allocated memory or NULL on failure
 */
void* memory_allocate(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
        return NULL;
    }
    
    return ptr;
}

/**
 * @brief Safe free with NULL pointer check
 * @param ptr Pointer to pointer to free
 */
void memory_free_safe(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

// ============================================================================
// HASH FUNCTIONS (from misc.c)
// ============================================================================

/**
 * @brief DJB2 hash function
 * @param key String to hash
 * @param capacity Hash table capacity
 * @return Hash value
 */
size_t xmd_hash_key(const char* key, size_t capacity) {
    if (!key || capacity == 0) {
        return 0;
    }
    
    unsigned long hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash % capacity;
}

/**
 * @brief Simple hash function for strings
 * @param key String key to hash
 * @return Hash value
 */
unsigned int hash_string(const char* key) {
    if (!key) {
        return 0;
    }
    
    unsigned int hash = 0;
    const char* p = key;
    
    while (*p) {
        hash = hash * 31 + *p;
        p++;
    }
    
    return hash;
}

/**
 * @brief Check if pointer is NULL with error message
 * @param ptr Pointer to check
 * @param error_msg Error message to display if NULL
 * @return true if NULL, false otherwise
 */
bool xmd_check_null(const void* ptr, const char* error_msg) {
    if (ptr == NULL) {
        if (error_msg) {
            fprintf(stderr, "Error: %s\n", error_msg);
        }
        return true;
    }
    return false;
}

/**
 * @brief Expand array capacity
 * @param array Pointer to array pointer
 * @param current_capacity Current capacity
 * @param element_size Size of each element
 * @return New capacity or 0 on failure
 */
size_t xmd_expand_array(void** array, size_t current_capacity, size_t element_size) {
    if (!array || element_size == 0) {
        return 0;
    }
    
    size_t new_capacity = current_capacity == 0 ? 1 : current_capacity * 2;
    void* new_array = xmd_realloc(*array, new_capacity * element_size);
    
    if (!new_array) {
        return 0;
    }
    
    *array = new_array;
    return new_capacity;
}

// ============================================================================
// STRING UTILITIES (from string.c)
// ============================================================================

/**
 * @brief Duplicate string safely
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* xmd_strdup(const char* str) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* dup = xmd_malloc(len + 1);
    if (!dup) {
        return NULL;
    }
    
    strcpy(dup, str);
    return dup;
}

/**
 * @brief String duplication with error handling
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* string_duplicate(const char* str) {
    return xmd_strdup(str);
}

/**
 * @brief Extract substring from string
 * @param source Source string
 * @param start Start position
 * @param length Length to extract
 * @return Extracted string or NULL on failure
 */
char* string_extract(const char* source, size_t start, size_t length) {
    if (!source) {
        return NULL;
    }
    
    size_t source_len = strlen(source);
    if (start >= source_len) {
        return NULL;
    }
    
    // Adjust length if it exceeds remaining string
    if (start + length > source_len) {
        length = source_len - start;
    }
    
    char* extracted = xmd_malloc(length + 1);
    if (!extracted) {
        return NULL;
    }
    
    strncpy(extracted, source + start, length);
    extracted[length] = '\0';
    
    return extracted;
}

/**
 * @brief Safe string copy with bounds checking
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * @return 0 on success, -1 on failure
 */
int xmd_strcpy_safe(char* dest, const char* src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) {
        return -1;
    }
    
    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return -1; // Not enough space
    }
    
    strcpy(dest, src);
    return 0;
}

/**
 * @brief Safe string concatenation with bounds checking
 * @param dest Destination buffer
 * @param src Source string to append
 * @param dest_size Size of destination buffer
 * @return 0 on success, -1 on failure
 */
int xmd_strcat_safe(char* dest, const char* src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) {
        return -1;
    }
    
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    
    if (dest_len + src_len >= dest_size) {
        return -1; // Not enough space
    }
    
    strcat(dest, src);
    return 0;
}

/**
 * @brief Trim whitespace from string
 * @param str String to trim (modified in place)
 * @return Trimmed string
 */
char* xmd_strtrim(char* str) {
    if (!str) {
        return NULL;
    }
    
    // Trim leading whitespace
    char* start = str;
    while (*start && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) {
        start++;
    }
    
    // Trim trailing whitespace
    char* end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
    
    // Move trimmed string to beginning if needed
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
    
    return str;
}
