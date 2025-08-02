/**
 * @file variable_new_boolean.c
 * @brief Create new boolean variable
 * 
 * This file contains ONLY the variable_new_boolean function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/variable.h"
#include "../../../utils/common/common_macros.h"
#include <stdlib.h>

/**
 * @brief Create new boolean variable
 * @param value Boolean value
 * @return New variable or NULL on error
 */
xmd_variable* variable_new_boolean(bool value) {
    xmd_variable* var = xmd_malloc(sizeof(xmd_variable));
    if (!var) {
        return NULL;
    }
    
    var->type = XMD_VAR_BOOLEAN;
    var->value.boolean_val = value;
    var->name = NULL;
    var->ref_count = 1;
    
    return var;
}