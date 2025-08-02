/**
 * @file variable_array_size.c
 * @brief Implementation of variable_array_size function
 * 
 * This file contains ONLY the variable_array_size function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stddef.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get array size
 * @param array_var Array variable
 * @return Array size or 0 if not array/invalid
 */

/**
 * @brief Get array size
 * @param array_var Array variable
 * @return Array size or 0 if not array/invalid
 */
size_t variable_array_size(const variable* array_var) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return 0;
    }
    
    return array_var->value.array_value->count;
}