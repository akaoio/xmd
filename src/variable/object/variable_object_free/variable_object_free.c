
/**
 * @file variable_object_free.c
 * @brief Implementation of variable_object_free function
 * 
 * This file contains ONLY the variable_object_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Free object contents (internal helper)
 * @param object_var Object variable
 */
void variable_object_free(variable* object_var) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value) {
        return;
    }
    
    variable_object* obj = object_var->value.object_value;
    for (size_t i = 0; i < obj->count; i++) {
        XMD_FREE_SAFE(obj->pairs[i].key);
        variable_unref(obj->pairs[i].value);
    }
    XMD_FREE_SAFE(obj->pairs);
    obj->pairs = NULL;
    obj->count = 0;
    obj->capacity = 0;
}
