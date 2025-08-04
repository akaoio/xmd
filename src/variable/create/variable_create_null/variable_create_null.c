
/**
 * @file variable_create_null.c
 * @brief Implementation of variable_create_null function
 * 
 * This file contains ONLY the variable_create_null function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"


/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    XMD_CREATE_VALIDATED(var, variable, sizeof(variable), NULL);
    var->type = VAR_NULL;
    var->ref_count = 1;
    return var;
}
