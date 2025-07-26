/**
 * @file variable_array_set.c
 * @brief Variable system implementation - array item setter
 * @author XMD Team
 *
 * Implementation of array item setter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Set item in array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @param item Item to set (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_set(variable* array_var, size_t index, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) return false;
    
    variable_unref(array->items[index]);
    array->items[index] = variable_ref(item);
    return true;
}
