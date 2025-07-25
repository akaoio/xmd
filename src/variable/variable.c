/**
 * @file variable.c
 * @brief Variable system implementation
 * @author XMD Team
 *
 * Implementation of variable creation, reference counting, type conversions,
 * and basic operations for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "variable.h"
#include "../../include/utils.h"

/* Forward declarations for extended functionality */
void variable_array_free(void* array);
void variable_object_free(void* obj);

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NULL;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new boolean variable
 * @param value Boolean value
 * @return New boolean variable or NULL on failure
 */
variable* variable_create_boolean(bool value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_BOOLEAN;
    var->value.boolean_value = value;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new number variable
 * @param value Numeric value
 * @return New number variable or NULL on failure
 */
variable* variable_create_number(double value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NUMBER;
    var->value.number_value = value;
    var->ref_count = 1;
    
    return var;
}

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
    var->value.array_value = NULL; // Simplified for now
    var->ref_count = 1;
    
    return var;
}

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
    var->value.object_value = NULL; // Simplified for now
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    var->ref_count++;
    return var;
}

/**
 * @brief Decrement reference count and destroy if zero
 * @param var Variable to unreference (can be NULL)
 */
void variable_unref(variable* var) {
    if (var == NULL) {
        return;
    }
    
    var->ref_count--;
    if (var->ref_count == 0) {
        switch (var->type) {
            case VAR_STRING:
                free(var->value.string_value);
                break;
            case VAR_ARRAY:
                variable_array_free(var->value.array_value);
                break;
            case VAR_OBJECT:
                variable_object_free(var->value.object_value);
                break;
            default:
                break;
        }
        free(var);
    }
}

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type or VAR_NULL if var is NULL
 */
variable_type variable_get_type(const variable* var) {
    return var ? var->type : VAR_NULL;
}

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (var == NULL) {
        return false;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return false;
        case VAR_BOOLEAN:
            return var->value.boolean_value;
        case VAR_NUMBER:
            return var->value.number_value != 0.0 && !isnan(var->value.number_value);
        case VAR_STRING:
            return var->value.string_value != NULL && strlen(var->value.string_value) > 0;
        case VAR_ARRAY:
        case VAR_OBJECT:
            return var->value.array_value != NULL || var->value.object_value != NULL;
        default:
            return false;
    }
}

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    return xmd_variable_to_number(var);
}

/**
 * @brief Convert variable to string
 * @param var Variable to convert
 * @return String representation (must be freed)
 */
char* variable_to_string(const variable* var) {
    if (var == NULL) {
        char* result = malloc(5);
        if (result) strcpy(result, "null");
        return result;
    }
    
    switch (var->type) {
        case VAR_NULL: {
            char* result = malloc(5);
            if (result) strcpy(result, "null");
            return result;
        }
        case VAR_BOOLEAN: {
            const char* str = var->value.boolean_value ? "true" : "false";
            char* result = malloc(strlen(str) + 1);
            if (result) strcpy(result, str);
            return result;
        }
        case VAR_NUMBER: {
            double num = var->value.number_value;
            if (isnan(num)) {
                char* result = malloc(4);
                if (result) strcpy(result, "NaN");
                return result;
            } else if (isinf(num)) {
                char* result = malloc(9);
                if (result) strcpy(result, num > 0 ? "Infinity" : "-Infinity");
                return result;
            } else if (num == floor(num) && num >= -2147483648.0 && num <= 2147483647.0) {
                char* result = malloc(32);
                if (result) snprintf(result, 32, "%.0f", num);
                return result;
            } else {
                char* result = malloc(32);
                if (result) snprintf(result, 32, "%.6g", num);
                return result;
            }
        }
        case VAR_STRING: {
            if (var->value.string_value == NULL) {
                char* result = malloc(1);
                if (result) result[0] = '\0';
                return result;
            }
            size_t len = strlen(var->value.string_value);
            char* result = malloc(len + 1);
            if (result) strcpy(result, var->value.string_value);
            return result;
        }
        case VAR_ARRAY: {
            char* result = malloc(3);
            if (result) strcpy(result, "[]");
            return result;
        }
        case VAR_OBJECT: {
            char* result = malloc(3);
            if (result) strcpy(result, "{}");
            return result;
        }
        default: {
            char* result = malloc(8);
            if (result) strcpy(result, "unknown");
            return result;
        }
    }
}

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b) {
    return xmd_variable_equals(a, b);
}

/**
 * @brief Create a deep copy of a variable
 * @param var Variable to copy
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return variable_create_null();
        case VAR_BOOLEAN:
            return variable_create_boolean(var->value.boolean_value);
        case VAR_NUMBER:
            return variable_create_number(var->value.number_value);
        case VAR_STRING:
            return variable_create_string(var->value.string_value);
        case VAR_ARRAY:
            return variable_create_array(); // Simplified
        case VAR_OBJECT:
            return variable_create_object(); // Simplified
        default:
            return NULL;
    }
}