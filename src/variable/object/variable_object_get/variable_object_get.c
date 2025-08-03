
/**
 * @file variable_object_get.c
 * @brief Implementation of variable_object_get function
 * 
 * This file contains ONLY the variable_object_get function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdint.h>
#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Get property from object variable
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    XMD_NULL_CHECK(object_var, NULL);
    XMD_NULL_CHECK(key, NULL);
    if (object_var->type != VAR_OBJECT) {
        return NULL;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    if (index == SIZE_MAX) {
        return NULL;
    }
    return object_var->value.object_value->pairs[index].value;
}
