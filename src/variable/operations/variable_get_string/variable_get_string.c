
/**
 * @file variable_get_string.c
 * @brief Implementation of variable_get_string function
 * 
 * This file contains ONLY the variable_get_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"
#include "utils/common/common_macros.h"

/**
 * @brief Get string value directly (convenience function)
 * @return String value or NULL if not string
 */
const char* variable_get_string(const variable* var) {
    if (!var) {
        XMD_ERROR_RETURN(NULL, "variable_get_string: NULL variable provided%s", "");
    }
    
    if (var->type != VAR_STRING) {
        XMD_ERROR_RETURN(NULL, "variable_get_string: Type conversion error - variable type %d is not VAR_STRING", var->type);
    }
    
    if (!var->value.string_value) {
        XMD_ERROR_RETURN(NULL, "variable_get_string: String variable contains NULL value%s", "");
    }
    
    return var->value.string_value;
}
