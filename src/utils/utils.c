/**
 * @file utils.c
 * @brief Common utility functions implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../../include/utils.h"
#include "../../include/variable.h"

/**
 * @brief Calculate hash for a string key using djb2 algorithm
 * @param key String key to hash
 * @param capacity Capacity of hash table (for modulo)
 * @return Hash value
 */
size_t xmd_hash_key(const char* key, size_t capacity) {
    if (key == NULL) {
        return 0;
    }
    
    size_t hash = 5381;
    while (*key) {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
        key++;
    }
    
    return hash % capacity;
}

/**
 * @brief Convert variable to number (double)
 * @param var Variable to convert
 * @return Numeric value or 0.0 if conversion fails
 */
double xmd_variable_to_number(const variable* var) {
    if (!var) {
        return 0.0;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return 0.0;
        case VAR_BOOLEAN:
            return var->value.boolean_value ? 1.0 : 0.0;
        case VAR_NUMBER:
            return var->value.number_value;
        case VAR_STRING:
            if (var->value.string_value) {
                char* endptr;
                double result = strtod(var->value.string_value, &endptr);
                return (*endptr == '\0') ? result : 0.0;
            }
            return 0.0;
        case VAR_ARRAY:
            // Arrays represent as 0.0 for now (could be length if structure was known)
            return 0.0;
        case VAR_OBJECT:
            // Objects represent as 0.0 for now (could be property count if structure was known)
            return 0.0;
        default:
            return 0.0;
    }
}

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if equal, false otherwise
 */
bool xmd_variable_equals(const variable* a, const variable* b) {
    if (!a || !b) {
        return (!a && !b);
    }
    
    if (a->type != b->type) {
        return false;
    }
    
    switch (a->type) {
        case VAR_NULL:
            return true;
        case VAR_BOOLEAN:
            return a->value.boolean_value == b->value.boolean_value;
        case VAR_NUMBER:
            // Use epsilon comparison for floating point numbers
            return fabs(a->value.number_value - b->value.number_value) < 1e-10;
        case VAR_STRING:
            if (!a->value.string_value && !b->value.string_value) {
                return true;
            }
            if (!a->value.string_value || !b->value.string_value) {
                return false;
            }
            return strcmp(a->value.string_value, b->value.string_value) == 0;
        case VAR_ARRAY:
            // For simplicity, arrays are equal only if they're the same instance
            return a->value.array_value == b->value.array_value;
        case VAR_OBJECT:
            // For simplicity, objects are equal only if they're the same instance
            return a->value.object_value == b->value.object_value;
        default:
            return false;
    }
}

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
 * @brief Safe calloc with NULL check
 * @param count Number of elements
 * @param size Size of each element
 * @return Allocated and zeroed memory or NULL on failure
 */
void* xmd_calloc(size_t count, size_t size) {
    if (count == 0 || size == 0) {
        return NULL;
    }
    return calloc(count, size);
}

/**
 * @brief Safe realloc with NULL check
 * @param ptr Existing pointer
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
 * @brief Safe string duplication
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* xmd_strdup(const char* str) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = xmd_malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

/**
 * @brief Expand array capacity safely
 * @param ptr Pointer to array pointer
 * @param current_capacity Current capacity
 * @param element_size Size of each element
 * @return New capacity or 0 on failure
 */
size_t xmd_expand_array(void** ptr, size_t current_capacity, size_t element_size) {
    if (!ptr || element_size == 0) {
        return 0;
    }
    
    // Double capacity or start with 8 if capacity is 0
    size_t new_capacity = current_capacity > 0 ? current_capacity * 2 : 8;
    
    void* new_ptr = xmd_realloc(*ptr, new_capacity * element_size);
    if (!new_ptr) {
        return 0;
    }
    
    *ptr = new_ptr;
    return new_capacity;
}

/**
 * @brief Check if pointer is NULL and handle error
 * @param ptr Pointer to check
 * @param error_msg Error message if NULL
 * @return true if NULL (error), false if valid
 */
bool xmd_check_null(const void* ptr, const char* error_msg) {
    if (!ptr) {
        if (error_msg) {
            fprintf(stderr, "Error: %s\n", error_msg);
        }
        return true;
    }
    return false;
}

/**
 * @brief Safe memory allocation with error logging
 * @param size Size to allocate
 * @param error_msg Error message context
 * @return Allocated memory or NULL on failure
 */
void* xmd_malloc_safe(size_t size, const char* error_msg) {
    void* ptr = xmd_malloc(size);
    if (!ptr && error_msg) {
        fprintf(stderr, "Memory allocation failed: %s (size: %zu)\n", 
                error_msg, size);
    }
    return ptr;
}