/**
 * @file variable_object_remove.c
 * @brief Variable object property removal function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "../../../include/variable.h"
#include "../../../include/variable_internal.h"

/**
 * @brief Remove property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return true if removed, false if not found/invalid
 */
bool variable_object_remove(variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return false;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t index = variable_object_find_key(object_var, key);
    
    if (index == SIZE_MAX) return false;
    
    // Free the pair
    free(object->pairs[index].key);
    variable_unref(object->pairs[index].value);
    
    // Move last pair to this position
    if (index < object->count - 1) {
        object->pairs[index] = object->pairs[object->count - 1];
    }
    object->count--;
    
    return true;
}