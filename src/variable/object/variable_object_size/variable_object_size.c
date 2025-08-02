
/**
 * @file variable_object_size.c
 * @brief Implementation of variable_object_size function
 * 
 * This file contains ONLY the variable_object_size function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stddef.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Get object property count
 * @return Property count or 0 if not object/invalid
 */
size_t variable_object_size(const variable* object_var) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value) {
        return 0;
    }
    
    return object_var->value.object_value->count;
}
