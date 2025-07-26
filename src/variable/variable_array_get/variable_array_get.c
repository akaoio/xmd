/**
 * @file variable_array_get.c
 * @brief Variable system implementation - array item getter
 * @author XMD Team
 *
 * Implementation of array item getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

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
    if (index >= array->count) return NULL;
    
    return array->items[index];
}
