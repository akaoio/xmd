/**
 * @file variable_create_object.c
 * @brief Variable system implementation - object creation
 * @author XMD Team
 *
 * Implementation of object variable creation for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create a new object variable
 * @return New empty object variable or NULL on failure
 */
variable* variable_create_object(void) {
    variable* var = malloc(sizeof(variable));
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
