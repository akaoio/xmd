
/**
 * @file variable_object_keys.c
 * @brief Implementation of variable_object_keys function
 * 
 * This file contains ONLY the variable_object_keys function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include <stdlib.h>
#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get all object keys
 * @return Array of key strings (must be freed) or NULL
 */
char** variable_object_keys(const variable* object_var, size_t* count) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    variable_object* obj = object_var->value.object_value;
    *count = obj->count;
    if (obj->count == 0) {
    char** keys = malloc(obj->count * sizeof(char*));
    if (!keys) {
        *count = 0;
    for (size_t i = 0; i < obj->count; i++) {
        keys[i] = strdup(obj->pairs[i].key);
        if (!keys[i]) {
            // Free previously allocated keys on failure
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            *count = 0;
            return NULL;
        }
    return keys;
}
}
}
}
