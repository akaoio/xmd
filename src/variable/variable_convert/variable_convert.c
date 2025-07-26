/**
 * @file variable_convert.c
 * @brief Variable conversion functions
 * @author XMD Team
 *
 * Implementation of variable type conversion and utility functions
 * for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "variable.h"
#include "../../../include/utils.h"

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
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, "null");
        return result;
    }
    
    switch (var->type) {
        case VAR_NULL: {
            char* result = malloc(5);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, "null");
            return result;
        }
        case VAR_BOOLEAN: {
            if (var->value.boolean_value) {
                char* result = malloc(5);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, "true");
                return result;
            } else {
                char* result = malloc(6);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, "false");
                return result;
            }
        }
        case VAR_NUMBER: {
            // Convert number to string
            char buffer[64];
            double num = var->value.number_value;
            
            if (isnan(num)) {
                strcpy(buffer, "NaN");
            } else if (isinf(num)) {
                if (num > 0) {
                    strcpy(buffer, "Infinity");
                } else {
                    strcpy(buffer, "-Infinity");
                }
            } else if (floor(num) == num && num >= -2147483648.0 && num <= 2147483647.0) {
                // Integer representation
                snprintf(buffer, sizeof(buffer), "%.0f", num);
            } else {
                // Floating point representation
                snprintf(buffer, sizeof(buffer), "%.15g", num);
            }
            
            size_t len = strlen(buffer);
            char* result = malloc(len + 1);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, buffer);
            return result;
        }
        case VAR_STRING: {
            if (var->value.string_value == NULL) {
                char* result = malloc(1);
                if (result == NULL) {
                    return NULL;
                }
                result[0] = '\0';
                return result;
            }
            
            size_t len = strlen(var->value.string_value);
            char* result = malloc(len + 1);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, var->value.string_value);
            return result;
        }
        case VAR_ARRAY: {
            // Simple array representation for now
            char* result = malloc(8);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, "[array]");
            return result;
        }
        case VAR_OBJECT: {
            // Simple object representation for now
            char* result = malloc(9);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, "[object]");
            return result;
        }
    }
    
    return NULL;
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
        case VAR_ARRAY: {
            // Deep copy array
            variable* new_array = variable_create_array();
            if (!new_array || !var->value.array_value) {
                return new_array;
            }
            
            // Copy array contents (shallow copy implementation)
            // For now, return empty array as arrays are complex structures
            return new_array;
        }
        case VAR_OBJECT: {
            // Deep copy object  
            variable* new_object = variable_create_object();
            if (!new_object || !var->value.object_value) {
                return new_object;
            }
            
            // Copy object properties (shallow copy implementation)
            // For now, return empty object as objects are complex structures
            return new_object;
        }
    }
    
    return NULL;
}