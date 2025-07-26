/**
 * @file variable_to_string.c
 * @brief Variable system implementation - string conversion
 * @author XMD Team
 *
 * Implementation of variable to string conversion for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

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
