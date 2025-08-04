
/**
 * @file variable_create_array.c
 * @brief Implementation of variable_create_array function
 * 
 * This file contains ONLY the variable_create_array function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Create a new array variable
 * @return New empty array variable or NULL on failure
 */
variable* variable_create_array(void) {
    XMD_CREATE_VALIDATED(var, variable, sizeof(variable), NULL);
    
    var->type = VAR_ARRAY;
    XMD_MALLOC_DYNAMIC(var->value.array_value, sizeof(variable_array), NULL);
    var->value.array_value->items = NULL;
    var->value.array_value->count = 0;
    var->value.array_value->capacity = 0;
    var->ref_count = 1;
    return var;
}
