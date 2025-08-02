/**
 * @file variable_create_string.c
 * @brief Implementation of variable_create_string function
 * 
 * This file contains ONLY the variable_create_string function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include <string.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create a new string variable
 * @param value String value (will be copied)
 * @return New string variable or NULL on failure
 */

/**
 * @brief Create a new string variable
 * @param value String value (will be copied)
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value) {
    variable* var = xmd_malloc(sizeof(variable));
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