/**
 * @file variable_ref.c
 * @brief Implementation of variable_ref function
 * 
 * This file contains ONLY the variable_ref function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    var->ref_count++;
    return var;
}