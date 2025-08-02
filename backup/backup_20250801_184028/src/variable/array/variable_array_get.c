/**
 * @file variable_array_get.c
 * @brief Implementation of variable_array_get function
 * 
 * This file contains ONLY the variable_array_get function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stddef.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get item from array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @return Item variable or NULL if not found/invalid
 */

/**
 * @brief Get item from array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @return Item variable or NULL if not found/invalid
 */
variable* variable_array_get(const variable* array_var, size_t index) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return NULL;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) {
        return NULL;
    }
    
    return array->items[index];
}