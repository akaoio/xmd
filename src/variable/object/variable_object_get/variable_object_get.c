
/**
 * @file variable_object_get.c
 * @brief Implementation of variable_object_get function
 * 
 * This file contains ONLY the variable_object_get function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get property from object variable
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !key) {
        return NULL;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    if (index == SIZE_MAX) {
    return object_var->value.object_value->pairs[index].value;
}
}
