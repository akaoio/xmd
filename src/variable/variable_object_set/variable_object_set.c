#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file variable_object_set.c
 * @brief Variable object property setter function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "../../../include/variable.h"

/**
 * @brief Set property in object variable
 * @param object_var Object variable
 * @param key Property key
 * @param value Property value (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_object_set(variable* object_var, const char* key, variable* value) {
    if (!object_var || object_var->type != VAR_OBJECT || !key || !value) {
        return false;
    }
    
    variable_object* obj = object_var->value.object_value;
    if (!obj) {
        return false;
    }
    
    // Check if key already exists
    size_t existing_index = variable_object_find_key(object_var, key);
    if (existing_index != SIZE_MAX) {
        // Update existing value
        variable_unref(obj->pairs[existing_index].value);
        obj->pairs[existing_index].value = variable_ref(value);
        return true;
    }
    
    // Add new key-value pair
    if (obj->count >= obj->capacity) {
        size_t new_capacity = obj->capacity == 0 ? 8 : obj->capacity * 2;
        variable_object_pair* new_pairs = realloc(obj->pairs, 
                                                 new_capacity * sizeof(variable_object_pair));
        if (!new_pairs) {
            return false;
        }
        obj->pairs = new_pairs;
        obj->capacity = new_capacity;
    }
    
    obj->pairs[obj->count].key = strdup(key);
    if (!obj->pairs[obj->count].key) {
        return false;
    }
    
    obj->pairs[obj->count].value = variable_ref(value);
    obj->count++;
    
    return true;
}