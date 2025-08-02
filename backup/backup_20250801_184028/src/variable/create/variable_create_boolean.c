/**
 * @file variable_create_boolean.c
 * @brief Implementation of variable_create_boolean function
 * 
 * This file contains ONLY the variable_create_boolean function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdlib.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create a new boolean variable
 * @param value Boolean value
 * @return New boolean variable or NULL on failure
 */

/**
 * @brief Create a new boolean variable
 * @param value Boolean value
 * @return New boolean variable or NULL on failure
 */
variable* variable_create_boolean(bool value) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_BOOLEAN;
    var->value.boolean_value = value;
    var->ref_count = 1;
    
    return var;
}