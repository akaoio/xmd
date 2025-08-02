/**
 * @file variable_create_consolidated.c
 * @brief Consolidated variable creation functions
 * 
 * This file contains unified variable creation with convenience wrappers.
 * Eliminates duplicate pattern across 6 create functions.
 * Genesis principle compliance - DRY elimination.
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"

/**
 * @brief Core variable creation function
 * @param type Variable type
 * @return New variable or NULL on failure
 */
static variable* variable_create_core(variable_type type) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = type;
    var->ref_count = 1;
    return var;
}

/**
 * @brief Create a new null variable
 */
variable* variable_create_null(void) {
    return variable_create_core(VAR_NULL);
}

/**
 * @brief Create a new boolean variable
 */
variable* variable_create_boolean(bool value) {
    variable* var = variable_create_core(VAR_BOOLEAN);
    if (var) {
        var->value.boolean_value = value;
    }
    return var;
}

/**
 * @brief Create a new number variable
 */
variable* variable_create_number(double value) {
    variable* var = variable_create_core(VAR_NUMBER);
    if (var) {
        var->value.number_value = value;
    }
    return var;
}

/**
 * @brief Create a new string variable
 */
variable* variable_create_string(const char* value) {
    variable* var = variable_create_core(VAR_STRING);
    if (!var) {
        return NULL;
    }
    
    if (value == NULL) {
        var->value.string_value = xmd_malloc(1);
        if (var->value.string_value == NULL) {
            xmd_free(var);
            return NULL;
        }
        var->value.string_value[0] = '\0';
    } else {
        size_t len = strlen(value);
        var->value.string_value = xmd_malloc(len + 1);
        if (var->value.string_value == NULL) {
            xmd_free(var);
            return NULL;
        }
        strcpy(var->value.string_value, value);
    }
    return var;
}

/**
 * @brief Create a new array variable
 */
variable* variable_create_array(void) {
    variable* var = variable_create_core(VAR_ARRAY);
    if (var) {
        var->value.array_value.elements = NULL;
        var->value.array_value.count = 0;
        var->value.array_value.capacity = 0;
    }
    return var;
}

/**
 * @brief Create a new object variable
 */
variable* variable_create_object(void) {
    variable* var = variable_create_core(VAR_OBJECT);
    if (var) {
        var->value.object_value.pairs = NULL;
        var->value.object_value.count = 0;
        var->value.object_value.capacity = 0;
    }
    return var;
}