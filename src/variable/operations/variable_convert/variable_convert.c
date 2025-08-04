/**
 * @file variable_convert.c
 * @brief Implementation of variable_convert function
 * 
 * This file contains ONLY the variable_convert function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdlib.h>

#include "variable.h"
#include "variable_internal.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Convert variable to different type
 * @param var Variable to convert
 * @param target_type Target type
 * @return Converted variable or NULL on error
 */
variable* variable_convert(variable* var, variable_type target_type) {
    XMD_VALIDATE_PTR_RETURN(var, NULL);
    
    // If already the target type, return a reference
    if (var->type == target_type) {
        return variable_ref(var);
    }
    
    // Use variable type dispatch macro instead of switch boilerplate
    if (target_type == VAR_BOOLEAN) {
        return variable_create_boolean(variable_to_boolean(var));
    } else if (target_type == VAR_NUMBER) {
        return variable_create_number(variable_to_number(var));
    } else if (target_type == VAR_STRING) {
        char* str = variable_to_string(var);
        XMD_VALIDATE_PTR_RETURN(str, NULL);
        variable* result = variable_create_string(str);
        XMD_FREE_SAFE(str);
        return result;
    } else if (target_type == VAR_NULL) {
        return variable_create_null();
    } else {
        return NULL; // Cannot convert to array/object types
    }
}