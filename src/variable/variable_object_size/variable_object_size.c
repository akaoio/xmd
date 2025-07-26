/**
 * @file variable_object_size.c
 * @brief Variable system implementation - object size getter
 * @author XMD Team
 *
 * Implementation of object size getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Get object property count
 * @param object_var Object variable
 * @return Property count or 0 if not object/invalid
 */
size_t variable_object_size(const variable* object_var) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value) {
        return 0;
    }
    
    return object_var->value.object_value->count;
}
