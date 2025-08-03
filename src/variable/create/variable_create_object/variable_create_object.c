
/**
 * @file variable_create_object.c
 * @brief Implementation of variable_create_object function
 * 
 * This file contains ONLY the variable_create_object function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create a new object variable
 * @return New empty object variable or NULL on failure
 */
variable* variable_create_object(void) {
    XMD_CREATE_VALIDATED(var, variable, sizeof(variable), NULL);
    
    var->type = VAR_OBJECT;
    var->value.object_value = xmd_malloc(sizeof(variable_object));
    if (!var->value.object_value) {
        XMD_FREE_SAFE(var);
        return NULL;
    }
    var->value.object_value->pairs = NULL;
    var->value.object_value->count = 0;
    var->value.object_value->capacity = 0;
    var->ref_count = 1;
    return var;
}
