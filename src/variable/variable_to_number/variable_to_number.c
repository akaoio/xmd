/**
 * @file variable_to_number.c
 * @brief Variable to number conversion function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../../include/variable.h"

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    if (!var) {
        return 0.0;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return 0.0;
            
        case VAR_BOOLEAN:
            return var->value.boolean_value ? 1.0 : 0.0;
            
        case VAR_NUMBER:
            return var->value.number_value;
            
        case VAR_STRING:
            if (!var->value.string_value) {
                return 0.0;
            }
            // Try to parse as number
            char* endptr;
            double result = strtod(var->value.string_value, &endptr);
            // If entire string was consumed, it's a valid number
            if (*endptr == '\0') {
                return result;
            }
            // If string is empty or just whitespace, return 0
            if (strlen(var->value.string_value) == 0) {
                return 0.0;
            }
            // Non-numeric string converts to NaN
            return NAN;
            
        case VAR_ARRAY:
            // Array length as number
            return var->value.array_value ? (double)var->value.array_value->count : 0.0;
            
        case VAR_OBJECT:
            // Object property count as number
            return var->value.object_value ? (double)var->value.object_value->count : 0.0;
            
        default:
            return 0.0;
    }
}
