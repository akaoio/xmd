/**
 * @file variable_equals.c
 * @brief Variable equality comparison function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/variable.h"

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b) {
    if (a == b) {
        return true; // Same pointer
    }
    
    if (!a || !b) {
        return false; // One is NULL
    }
    
    if (a->type != b->type) {
        return false; // Different types
    }
    
    switch (a->type) {
        case VAR_NULL:
            return true; // Both are NULL type
            
        case VAR_BOOLEAN:
            return a->value.boolean_value == b->value.boolean_value;
            
        case VAR_NUMBER:
            return a->value.number_value == b->value.number_value;
            
        case VAR_STRING:
            if (!a->value.string_value && !b->value.string_value) {
                return true;
            }
            if (!a->value.string_value || !b->value.string_value) {
                return false;
            }
            return strcmp(a->value.string_value, b->value.string_value) == 0;
            
        case VAR_ARRAY:
            // For now, array comparison is by reference
            return a->value.array_value == b->value.array_value;
            
        case VAR_OBJECT:
            // For now, object comparison is by reference
            return a->value.object_value == b->value.object_value;
            
        default:
            return false;
    }
}
