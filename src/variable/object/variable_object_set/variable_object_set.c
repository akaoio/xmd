
/**
 * @file variable_object_set.c
 * @brief Implementation of variable_object_set function
 * 
 * This file contains ONLY the variable_object_set function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Set property in object variable
 * @return true on success, false on failure
 */
bool variable_object_set(variable* object_var, const char* key, variable* value) {
    XMD_NULL_CHECK_RETURN(object_var, false);
    XMD_NULL_CHECK_RETURN(key, false);
    XMD_NULL_CHECK_RETURN(value, false);
    if (object_var->type != VAR_OBJECT) {
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
        variable_object_pair* new_pairs = xmd_realloc(obj->pairs, 
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
