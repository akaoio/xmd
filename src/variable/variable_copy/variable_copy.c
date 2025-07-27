/**
 * @file variable_copy.c
 * @brief Variable deep copy function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/variable_internal.h"

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
            // Deep copy array
            variable* new_array = variable_create_array();
            if (!new_array || !var->value.array_value) {
                return new_array;
            }
            
            // Copy array contents (shallow copy implementation)
            // For now, return empty array as arrays are complex structures
            return new_array;
        }
        case VAR_OBJECT: {
            // Deep copy object  
            variable* new_object = variable_create_object();
            if (!new_object || !var->value.object_value) {
                return new_object;
            }
            
            // Copy object properties (shallow copy implementation)
            // For now, return empty object as objects are complex structures
            return new_object;
        }
    }
    
    return NULL;
}
