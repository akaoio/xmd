
/**
 * @file variable_create_null.c
 * @brief Implementation of variable_create_null function
 * 
 * This file contains ONLY the variable_create_null function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "variable.h"
#include "variable_internal.h"


/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NULL;
    var->ref_count = 1;
    return var;
}
