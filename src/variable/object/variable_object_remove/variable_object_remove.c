
/**
 * @file variable_object_remove.c
 * @brief Implementation of variable_object_remove function
 * 
 * This file contains ONLY the variable_object_remove function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "utils/common/common_macros.h"

/**
 * @brief Remove property from object variable
 * @return true if removed, false if not found/invalid
 */
bool variable_object_remove(variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !key) {
        return false;
    }
    
    variable_object* obj = object_var->value.object_value;
    if (!obj) {
        return false;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    if (index == SIZE_MAX) {
        return false;
    }
    
    // Free the key and unreference the value
    XMD_FREE_SAFE(obj->pairs[index].key);
    variable_unref(obj->pairs[index].value);
    
    // Shift remaining pairs down
    for (size_t i = index; i < obj->count - 1; i++) {
        obj->pairs[i] = obj->pairs[i + 1];
    }
    
    obj->count--;
    return true;
}
