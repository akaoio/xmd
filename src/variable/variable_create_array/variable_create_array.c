/**
 * @file variable_create_array.c
 * @brief Variable system implementation - array creation
 * @author XMD Team
 *
 * Implementation of array variable creation for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create a new array variable
 * @return New empty array variable or NULL on failure
 */
variable* variable_create_array(void) {
    variable* var = malloc(sizeof(variable));
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
