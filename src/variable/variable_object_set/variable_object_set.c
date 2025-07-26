/**
 * @file variable_object_set.c
 * @brief Variable system implementation - object property setter
 * @author XMD Team
 *
 * Implementation of object property setter for the XMD variable system.
 * Includes helper function for key finding.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Find pair index by key
 * @param object Object to search
 * @param key Key to find
 * @return Index if found, SIZE_MAX if not found
 */
static size_t variable_object_find_key(const variable_object* object, const char* key) {
    if (!object || !key) return SIZE_MAX;
    
    for (size_t i = 0; i < object->count; i++) {
        if (strcmp(object->pairs[i].key, key) == 0) {
            return i;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Set property in object variable
 * @param object_var Object variable
 * @param key Property key
 * @param value Property value (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_object_set(variable* object_var, const char* key, variable* value) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return false;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t existing_index = variable_object_find_key(object, key);
    
    if (existing_index != SIZE_MAX) {
        // Update existing
        variable_unref(object->pairs[existing_index].value);
        object->pairs[existing_index].value = variable_ref(value);
        return true;
    }
    
    // Add new pair
    if (object->count >= object->capacity) {
        size_t new_capacity = object->capacity == 0 ? 4 : object->capacity * 2;
        variable_object_pair* new_pairs = realloc(object->pairs, new_capacity * sizeof(variable_object_pair));
        if (!new_pairs) return false;
        
        object->pairs = new_pairs;
        object->capacity = new_capacity;
    }
    
    object->pairs[object->count].key = strdup(key);
    if (!object->pairs[object->count].key) return false;
    
    object->pairs[object->count].value = variable_ref(value);
    object->count++;
    return true;
}
