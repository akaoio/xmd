
/**
 * @file variable_array_add.c
 * @brief Implementation of variable_array_add function
 * 
 * This file contains ONLY the variable_array_add function.
 * One function per file - Genesis principle compliance.  
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../include/utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Add item to array variable
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !item) {
        return false;
    }
    XMD_VALIDATE_PTR_RETURN(array_var->value.array_value, false);
    
    variable_array* array = array_var->value.array_value;
    // Resize if needed
    if (array->count >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        XMD_REALLOC_VALIDATED(array->items, variable*, new_capacity * sizeof(variable*), false);
        array->capacity = new_capacity;
    }
    
    array->items[array->count++] = variable_ref(item);
    return true;
}
