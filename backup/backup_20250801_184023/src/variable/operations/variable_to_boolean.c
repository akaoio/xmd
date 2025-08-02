/**
 * @file variable_to_boolean.c
 * @brief Implementation of variable_to_boolean function
 * 
 * This file contains ONLY the variable_to_boolean function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <string.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (!var) {
        return false;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return false;
            
        case VAR_BOOLEAN:
            return var->value.boolean_value;
            
        case VAR_NUMBER:
            return var->value.number_value != 0.0 && !isnan(var->value.number_value);
            
        case VAR_STRING:
            return var->value.string_value && strlen(var->value.string_value) > 0;
            
        case VAR_ARRAY:
            return var->value.array_value && var->value.array_value->count > 0;
            
        case VAR_OBJECT:
            return var->value.object_value && var->value.object_value->count > 0;
    }
    
    return false;
}