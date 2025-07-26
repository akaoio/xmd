/**
 * @file variable_create_string.c
 * @brief Variable system implementation - string creation
 * @author XMD Team
 *
 * Implementation of string variable creation for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create a new string variable
 * @param value String value (will be copied)
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_STRING;
    var->ref_count = 1;
    
    if (value == NULL) {
        var->value.string_value = malloc(1);
        if (var->value.string_value == NULL) {
            free(var);
            return NULL;
        }
        var->value.string_value[0] = '\0';
    } else {
        size_t len = strlen(value);
        var->value.string_value = malloc(len + 1);
        if (var->value.string_value == NULL) {
            free(var);
            return NULL;
        }
        strcpy(var->value.string_value, value);
    }
    
    return var;
}
