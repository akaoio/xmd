
/**
 * @file variable_to_number.c
 * @brief Implementation of variable_to_number function
 * 
 * This file contains ONLY the variable_to_number function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Convert variable to number
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    if (!var) return 0.0;
    
    double result = 0.0;
    
    XMD_VARIABLE_TYPE_DISPATCH(var,
        /* VAR_STRING */
        {
            if (!var->value.string_value) {
                result = 0.0;
            } else {
                char* endptr;
                result = strtod(var->value.string_value, &endptr);
                // If conversion failed or there are remaining characters
                if (endptr == var->value.string_value || *endptr != '\0') {
                    result = 0.0;
                }
            }
        },
        
        /* VAR_NUMBER */
        result = var->value.number_value,
        
        /* VAR_BOOLEAN */
        result = var->value.boolean_value ? 1.0 : 0.0,
        
        /* VAR_ARRAY */
        result = var->value.array_value ? (double)var->value.array_value->count : 0.0,
        
        /* VAR_OBJECT */
        result = var->value.object_value ? (double)var->value.object_value->count : 0.0,
        
        /* VAR_NULL */
        result = 0.0,
        
        /* default */
        result = 0.0
    );
    
    return result;
}
