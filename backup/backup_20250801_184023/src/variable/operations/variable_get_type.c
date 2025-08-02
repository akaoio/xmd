/**
 * @file variable_get_type.c
 * @brief Implementation of variable_get_type function
 * 
 * This file contains ONLY the variable_get_type function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type
 */

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type
 */
variable_type variable_get_type(const variable* var) {
    if (!var) {
        return VAR_NULL;
    }
    
    return var->type;
}