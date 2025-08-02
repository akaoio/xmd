/**
 * @file variable_new_number.c
 * @brief Create new number variable
 * 
 * This file contains ONLY the variable_new_number function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/variable.h"
#include "../../../utils/common/common_macros.h"
#include <stdlib.h>

/**
 * @brief Create new number variable
 * @param value Number value
 * @return New variable or NULL on error
 */
xmd_variable* variable_new_number(double value) {
    xmd_variable* var = xmd_malloc(sizeof(xmd_variable));
    if (!var) {
        return NULL;
    }
    
    var->type = XMD_VAR_NUMBER;
    var->value.number_val = value;
    var->name = NULL;
    var->ref_count = 1;
    
    return var;
}