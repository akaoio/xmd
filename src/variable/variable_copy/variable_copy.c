/**
 * @file variable_copy.c
 * @brief Variable system implementation - deep copy
 * @author XMD Team
 *
 * Implementation of variable deep copy for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create a deep copy of a variable
 * @param var Variable to copy
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return variable_create_null();
        case VAR_BOOLEAN:
            return variable_create_boolean(var->value.boolean_value);
        case VAR_NUMBER:
            return variable_create_number(var->value.number_value);
        case VAR_STRING:
            return variable_create_string(var->value.string_value);
        case VAR_ARRAY: {
            variable* new_array = variable_create_array();
            if (!new_array || !var->value.array_value) return new_array;
            
            // Deep copy array items
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                variable* item_copy = variable_copy(var->value.array_value->items[i]);
                if (item_copy) {
                    variable_array_add(new_array, item_copy);
                    variable_unref(item_copy); // Release our reference, array holds it
                }
            }
            return new_array;
        }
        case VAR_OBJECT: {
            variable* new_object = variable_create_object();
            if (!new_object || !var->value.object_value) return new_object;
            
            // Deep copy object properties
            for (size_t i = 0; i < var->value.object_value->count; i++) {
                const variable_object_pair* pair = &var->value.object_value->pairs[i];
                variable* value_copy = variable_copy(pair->value);
                if (value_copy) {
                    variable_object_set(new_object, pair->key, value_copy);
                    variable_unref(value_copy); // Release our reference, object holds it
                }
            }
            return new_object;
        }
        default:
            return NULL;
    }
}
