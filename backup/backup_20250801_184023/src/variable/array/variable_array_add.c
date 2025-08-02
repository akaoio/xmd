/**
 * @file variable_array_add.c
 * @brief Implementation of variable_array_add function
 * 
 * This file contains ONLY the variable_array_add function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdbool.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */

/**
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value || !item) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    
    // Resize if needed
    if (array->count >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        variable** new_items = xmd_realloc(array->items, new_capacity * sizeof(variable*));
        if (!new_items) return false;
        
        array->items = new_items;
        array->capacity = new_capacity;
    }
    
    array->items[array->count++] = variable_ref(item);
    return true;
}