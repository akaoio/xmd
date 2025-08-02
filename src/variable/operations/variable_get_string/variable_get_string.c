
/**
 * @file variable_get_string.c
 * @brief Implementation of variable_get_string function
 * 
 * This file contains ONLY the variable_get_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get string value directly (convenience function)
 * @return String value or NULL if not string
 */
const char* variable_get_string(const variable* var) {
    if (!var || var->type != VAR_STRING) {
        return NULL;
    }
    return var->value.string_value;
}
