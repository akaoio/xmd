
/**
 * @file variable_create_array.c
 * @brief Implementation of variable_create_array function
 * 
 * This file contains ONLY the variable_create_array function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create a new array variable
 * @return New empty array variable or NULL on failure
 */
variable* variable_create_array(void) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_ARRAY;
    var->value.array_value = malloc(sizeof(variable_array));
    if (!var->value.array_value) {
        free(var);
        return NULL;
    }
    var->value.array_value->items = NULL;
    var->value.array_value->count = 0;
    var->value.array_value->capacity = 0;
    var->ref_count = 1;
    return var;
}
