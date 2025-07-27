/**
 * @file variable_object_get.c
 * @brief Variable object property getter function
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
 * @brief Get property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return NULL;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    
    if (index == SIZE_MAX) return NULL;
    return object_var->value.object_value->pairs[index].value;
}