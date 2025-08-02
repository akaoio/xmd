
/**
 * @file variable_array_set.c
 * @brief Implementation of variable_array_set function
 * 
 * This file contains ONLY the variable_array_set function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <stddef.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Set item in array variable by index
 * @return true on success, false on failure
 */
bool variable_array_set(variable* array_var, size_t index, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value || !item) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) {
        return false;
    }
    // Unreference old item and set new one
    variable_unref(array->items[index]);
    array->items[index] = variable_ref(item);
    return true;
}
