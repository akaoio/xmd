/**
 * @file variable_to_string.c
 * @brief Variable to string conversion function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"

/**
 * @brief Convert variable to string
 * @param var Variable to convert
 * @return String representation (must be freed)
 */
char* variable_to_string(const variable* var) {
    if (var == NULL) {
        char* result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
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
