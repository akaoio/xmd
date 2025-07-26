/**
 * @file variable_get_number.c
 * @brief Get number value directly (convenience function)
 * @author XMD Team
 */

#include "../../../../include/variable_extended_internal.h"

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