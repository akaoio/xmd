/**
 * @file xmd_variable_equals.c
 * @brief Variable equality comparison function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if equal, false otherwise
 */
bool xmd_variable_equals(const variable* a, const variable* b) {
    if (!a || !b) {
        return (!a && !b);
    }
    
    if (a->type != b->type) {
        return false;
    }
    
    switch (a->type) {
        case VAR_NULL:
            return true;
        case VAR_BOOLEAN:
            return a->value.boolean_value == b->value.boolean_value;
        case VAR_NUMBER:
            // Use epsilon comparison for floating point numbers
            return fabs(a->value.number_value - b->value.number_value) < 1e-10;
        case VAR_STRING:
            if (!a->value.string_value && !b->value.string_value) {
                return true;
            }
            if (!a->value.string_value || !b->value.string_value) {
                return false;
            }
            return strcmp(a->value.string_value, b->value.string_value) == 0;
        case VAR_ARRAY:
            // For simplicity, arrays are equal only if they're the same instance
            return a->value.array_value == b->value.array_value;
        case VAR_OBJECT:
            // For simplicity, objects are equal only if they're the same instance
            return a->value.object_value == b->value.object_value;
        default:
            return false;
    }
}