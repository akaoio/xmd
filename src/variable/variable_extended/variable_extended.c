/**
 * @file variable_extended.c
 * @brief Extended variable system implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "variable.h"

/* Use definitions from variable.h - no duplicate typedefs needed */

/**
 * @brief Get boolean value directly (convenience function)
 * @param var Variable to get boolean from
 * @return Boolean value or false if not boolean
 */
bool variable_get_boolean(const variable* var) {
    if (!var || var->type != VAR_BOOLEAN) {
        return false;
    }
    return var->value.boolean_value;
}

/**
 * @brief Get number value directly (convenience function)
 * @param var Variable to get number from
 * @return Number value or 0.0 if not number
 */
double variable_get_number(const variable* var) {
    if (!var || var->type != VAR_NUMBER) {
        return 0.0;
    }
    return var->value.number_value;
}

/**
 * @brief Get string value directly (convenience function)
 * @param var Variable to get string from
 * @return String value or NULL if not string
 */
const char* variable_get_string(const variable* var) {
    if (!var || var->type != VAR_STRING) {
        return NULL;
    }
    return var->value.string_value;
}

/* Array functions are implemented in variable.c - using those implementations */

/* Object functions are implemented in variable.c - using those implementations */

/* Free functions are internal and implemented in variable.c */