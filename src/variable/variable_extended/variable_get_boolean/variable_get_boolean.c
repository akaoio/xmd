/**
 * @file variable_get_boolean.c
 * @brief Get boolean value directly (convenience function)
 * @author XMD Team
 */

#include "../../../../include/variable_extended_internal.h"

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