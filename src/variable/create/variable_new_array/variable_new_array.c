
/**
 * @file variable_new_array.c
 * @brief Implementation of variable_new_array function
 * 
 * This file contains ONLY the variable_new_array function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create array with initial items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count) {
    variable* array_var = variable_create_array();
    if (!array_var) {
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (!variable_array_add(array_var, items[i])) {
            variable_unref(array_var);
            return NULL;
        }
    }
    return array_var;
}
