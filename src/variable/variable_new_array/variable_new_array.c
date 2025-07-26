/**
 * @file variable_new_array.c
 * @brief Variable system implementation - array creation with initial items
 * @author XMD Team
 *
 * Implementation of array creation with initial items for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create array with initial items
 * @param items Array of variable pointers
 * @param count Number of items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count) {
    variable* array_var = variable_create_array();
    if (!array_var || !items) {
        return array_var;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (!variable_array_add(array_var, items[i])) {
            variable_unref(array_var);
            return NULL;
        }
    }
    
    return array_var;
}
