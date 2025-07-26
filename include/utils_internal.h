/**
 * @file utils_internal.h
 * @brief Internal header for utils functions
 * @author XMD Team
 */

#ifndef UTILS_INTERNAL_H
#define UTILS_INTERNAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "utils.h"
#include "variable.h"

// Function declarations
size_t xmd_hash_key(const char* key, size_t capacity);
double xmd_variable_to_number(const variable* var);
bool xmd_variable_equals(const variable* a, const variable* b);
void* xmd_malloc(size_t size);
void* xmd_calloc(size_t count, size_t size);
void* xmd_realloc(void* ptr, size_t size);
char* xmd_strdup(const char* str);
size_t xmd_expand_array(void** ptr, size_t current_capacity, size_t element_size);
bool xmd_check_null(const void* ptr, const char* error_msg);
void* xmd_malloc_safe(size_t size, const char* error_msg);

#endif /* UTILS_INTERNAL_H */