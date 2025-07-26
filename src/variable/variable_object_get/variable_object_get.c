/**
 * @file variable_object_get.c
 * @brief Variable system implementation - object property getter
 * @author XMD Team
 *
 * Implementation of object property getter for the XMD variable system.
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
 * @brief Get property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return NULL;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t index = variable_object_find_key(object, key);
    
    if (index == SIZE_MAX) return NULL;
    return object->pairs[index].value;
}
