
/**
 * @file variable_to_boolean.c
 * @brief Implementation of variable_to_boolean function
 * 
 * This file contains ONLY the variable_to_boolean function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Convert variable to boolean
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (!var) return false;
    
    bool result = false;
    
    XMD_VARIABLE_TYPE_DISPATCH(var,
        /* VAR_STRING */
        result = var->value.string_value && strlen(var->value.string_value) > 0,
        
        /* VAR_NUMBER */
        result = var->value.number_value != 0.0 && !isnan(var->value.number_value),
        
        /* VAR_BOOLEAN */
        result = var->value.boolean_value,
        
        /* VAR_ARRAY */
        result = var->value.array_value && var->value.array_value->count > 0,
        
        /* VAR_OBJECT */
        result = var->value.object_value && var->value.object_value->count > 0,
        
        /* VAR_NULL */
        result = false,
        
        /* default */
        result = false
    );
    
    return result;
}
