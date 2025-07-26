/**
 * @file variable_array_add.c
 * @brief Variable system implementation - array item addition
 * @author XMD Team
 *
 * Implementation of array item addition for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    
    // Resize if needed
    if (array->count >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        variable** new_items = realloc(array->items, new_capacity * sizeof(variable*));
        if (!new_items) return false;
        
        array->items = new_items;
        array->capacity = new_capacity;
    }
    
    array->items[array->count++] = variable_ref(item);
    return true;
}
