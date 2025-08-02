/**
 * @file variable_object_find_key.c
 * @brief Implementation of variable_object_find_key function
 * 
 * This file contains ONLY the variable_object_find_key function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include <string.h>

#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Find key index in object variable (internal helper)
 * @param object_var Object variable
 * @param key Key to find
 * @return Key index or SIZE_MAX if not found
 */

/**
 * @brief Find key index in object variable (internal helper)
 * @param object_var Object variable
 * @param key Key to find
 * @return Key index or SIZE_MAX if not found
 */
size_t variable_object_find_key(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return SIZE_MAX;
    }
    
    variable_object* obj = object_var->value.object_value;
    for (size_t i = 0; i < obj->count; i++) {
        if (strcmp(obj->pairs[i].key, key) == 0) {
            return i;
        }
    }
    
    return SIZE_MAX;
}