/**
 * @file variable_object_free.c
 * @brief Variable object cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/variable_internal.h"

/**
 * @brief Free object structure and all its pairs
 * @param object Object to free
 */
void variable_object_free(variable_object* object) {
    if (!object) return;
    
    // Free all pairs
    for (size_t i = 0; i < object->count; i++) {
        free(object->pairs[i].key);
        variable_unref(object->pairs[i].value);
    }
    
    free(object->pairs);
    free(object);
}