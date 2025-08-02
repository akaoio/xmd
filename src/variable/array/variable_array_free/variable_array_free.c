
/**
 * @file variable_array_free.c
 * @brief Implementation of variable_array_free function
 * 
 * This file contains ONLY the variable_array_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"

/**
 * @brief Free array contents (internal helper)
 * @param array_var Array variable
 */
void variable_array_XMD_FREE_SAFE(variable* array_var) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return;
    }
    
    variable_array* array = array_var->value.array_value;
    for (size_t i = 0; i < array->count; i++) {
        variable_unref(array->items[i]);
    }
    XMD_FREE_SAFE(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}
