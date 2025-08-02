
/**
 * @file variable_create_object.c
 * @brief Implementation of variable_create_object function
 * 
 * This file contains ONLY the variable_create_object function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create a new object variable
 * @return New empty object variable or NULL on failure
 */
variable* variable_create_object(void) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_OBJECT;
    var->value.object_value = malloc(sizeof(variable_object));
    if (!var->value.object_value) {
        free(var);
        return NULL;
    }
    var->value.object_value->pairs = NULL;
    var->value.object_value->count = 0;
    var->value.object_value->capacity = 0;
    var->ref_count = 1;
    return var;
}
