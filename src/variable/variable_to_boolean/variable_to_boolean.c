/**
 * @file variable_to_boolean.c
 * @brief Variable system implementation - boolean conversion
 * @author XMD Team
 *
 * Implementation of variable to boolean conversion for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (var == NULL) {
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
            return var->value.string_value != NULL && strlen(var->value.string_value) > 0;
        case VAR_ARRAY:
        case VAR_OBJECT:
            return var->value.array_value != NULL || var->value.object_value != NULL;
        default:
            return false;
    }
}
