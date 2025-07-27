/**
 * @file variable_array_free.c
 * @brief Variable array cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/variable_internal.h"

/**
 * @brief Free array structure and all its items
 * @param array Array to free
 */
void variable_array_free(variable_array* array) {
    if (!array) return;
    
    // Unref all items
    for (size_t i = 0; i < array->count; i++) {
        variable_unref(array->items[i]);
    }
    
    free(array->items);
    free(array);
}