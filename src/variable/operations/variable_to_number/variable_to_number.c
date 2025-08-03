
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
#include "../../../utils/common/common_macros.h"

/**
 * @brief Convert variable to number
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    XMD_VALIDATE_PTRS(0.0, var);
    
    switch (var->type) {
        case VAR_NULL:
            return 0.0;
            
        case VAR_BOOLEAN:
            return var->value.boolean_value ? 1.0 : 0.0;
        case VAR_NUMBER:
            return var->value.number_value;
        case VAR_STRING:
            if (!var->value.string_value) return 0.0;
            char* endptr;
            double result = strtod(var->value.string_value, &endptr);
            // If conversion failed or there are remaining characters
            if (endptr == var->value.string_value || *endptr != '\0') {
                return 0.0;
            }
            return result;
        case VAR_ARRAY:
            return var->value.array_value ? (double)var->value.array_value->count : 0.0;
        case VAR_OBJECT:
            return var->value.object_value ? (double)var->value.object_value->count : 0.0;
    return 0.0;
}
}
