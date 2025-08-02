/**
 * @file variable_get_number.c
 * @brief Implementation of variable_get_number function
 * 
 * This file contains ONLY the variable_get_number function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get number value directly (convenience function)
 * @param var Variable to get number from
 * @return Number value or 0.0 if not number
 */

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