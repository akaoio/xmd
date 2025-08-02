/**
 * @file variable_get_boolean.c
 * @brief Implementation of variable_get_boolean function
 * 
 * This file contains ONLY the variable_get_boolean function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdbool.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get boolean value directly (convenience function)
 * @param var Variable to get boolean from
 * @return Boolean value or false if not boolean
 */

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