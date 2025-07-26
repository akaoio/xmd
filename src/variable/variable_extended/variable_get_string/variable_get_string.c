/**
 * @file variable_get_string.c
 * @brief Get string value directly (convenience function)
 * @author XMD Team
 */

#include "../../../../include/variable_extended_internal.h"

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