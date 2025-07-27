/**
 * @file variable_object_find_key.c
 * @brief Variable object key finder function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stddef.h>
#include "../../../include/variable.h"
#include "../../../include/variable_internal.h"

/**
 * @brief Find key index in object variable
 * @param object_var Object variable
 * @param key Key to find
 * @return Key index or SIZE_MAX if not found
 */
size_t variable_object_find_key(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !key) {
        return SIZE_MAX;
    }
    
    variable_object* obj = object_var->value.object_value;
    if (!obj) {
        return SIZE_MAX;
    }
    
    for (size_t i = 0; i < obj->count; i++) {
        if (obj->pairs[i].key && strcmp(obj->pairs[i].key, key) == 0) {
            return i;
        }
    }
    
    return SIZE_MAX;
}