/**
 * @file variable_object_find_key.c
 * @brief Implementation of variable_object_find_key function
 * 
 * This file contains ONLY the variable_object_find_key function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"

/**
 * @brief Find key index in object (internal helper)
 * @param object_var Object variable
 * @param key Key to find
 * @return Index or SIZE_MAX if not found
 */
size_t variable_object_find_key(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || 
        !object_var->value.object_value || !key) {
        return SIZE_MAX;
    }
    
    variable_object* obj = object_var->value.object_value;
    for (size_t i = 0; i < obj->count; i++) {
        if (STR_EQUALS(obj->pairs[i].key, key)) {
            return i;
        }
    }
    return SIZE_MAX;
}
