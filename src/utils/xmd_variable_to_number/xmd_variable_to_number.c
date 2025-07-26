/**
 * @file xmd_variable_to_number.c
 * @brief Variable to number conversion function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Convert variable to number (double)
 * @param var Variable to convert
 * @return Numeric value or 0.0 if conversion fails
 */
double xmd_variable_to_number(const variable* var) {
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
            if (var->value.string_value) {
                char* endptr;
                double result = strtod(var->value.string_value, &endptr);
                return (*endptr == '\0') ? result : 0.0;
            }
            return 0.0;
        case VAR_ARRAY:
            // Arrays represent as 0.0 for now (could be length if structure was known)
            return 0.0;
        case VAR_OBJECT:
            // Objects represent as 0.0 for now (could be property count if structure was known)
            return 0.0;
        default:
            return 0.0;
    }
}