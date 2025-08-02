
/**
 * @file variable_array_length.c
 * @brief Implementation of variable_array_length function
 * 
 * This file contains ONLY the variable_array_length function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get array length (alias for size)
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var) {
    return variable_array_size(var);
}
