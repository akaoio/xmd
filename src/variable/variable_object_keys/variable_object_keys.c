#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file variable_object_keys.c
 * @brief Variable system implementation - object keys getter
 * @author XMD Team
 *
 * Implementation of object keys getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Get all object keys
 * @param object_var Object variable
 * @param count Output for key count
 * @return Array of key strings (must be freed) or NULL
 */
char** variable_object_keys(const variable* object_var, size_t* count) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    variable_object* object = object_var->value.object_value;
    *count = object->count;
    
    if (object->count == 0) return NULL;
    
    char** keys = malloc(object->count * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < object->count; i++) {
        keys[i] = strdup(object->pairs[i].key);
        if (!keys[i]) {
            // Cleanup on failure
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            *count = 0;
            return NULL;
        }
    }
    
    return keys;
}
