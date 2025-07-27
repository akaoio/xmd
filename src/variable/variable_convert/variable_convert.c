/**
 * @file variable_convert.c
 * @brief Variable conversion functions
 * @author XMD Team
 *
 * Implementation of variable type conversion and utility functions
 * for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable.h"

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type
 */
variable_type variable_get_type(const variable* var) {
    if (!var) {
        return VAR_NULL;
    }
    
    return var->type;
}

/**
 * @brief Convert variable to different type
 * @param var Variable to convert
 * @param target_type Target type
 * @return Converted variable or NULL on error
 */
variable* variable_convert(variable* var, variable_type target_type) {
    if (!var) {
        return NULL;
    }
    
    // If already the target type, return a reference
    if (var->type == target_type) {
        return variable_ref(var);
    }
    
    switch (target_type) {
        case VAR_BOOLEAN:
            return variable_create_boolean(variable_to_boolean(var));
            
        case VAR_NUMBER:
            return variable_create_number(variable_to_number(var));
            
        case VAR_STRING: {
            char* str = variable_to_string(var);
            if (!str) return NULL;
            variable* result = variable_create_string(str);
            free(str);
            return result;
        }
        
        case VAR_NULL:
            return variable_create_null();
            
        default:
            return NULL; // Cannot convert to array/object types
    }
}


