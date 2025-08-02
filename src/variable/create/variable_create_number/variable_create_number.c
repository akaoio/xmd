
/**
 * @file variable_create_number.c
 * @brief Implementation of variable_create_number function
 * 
 * This file contains ONLY the variable_create_number function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Create a new number variable
 * @return New number variable or NULL on failure
 */
variable* variable_create_number(double value) {
    variable* var;
    XMD_MALLOC_CHECK(var, sizeof(variable));
    
    var->type = VAR_NUMBER;
    var->value.number_value = value;
    var->ref_count = 1;
    return var;
}
