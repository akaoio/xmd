
/**
 * @file variable_to_string.c
 * @brief Implementation of variable_to_string function
 * 
 * This file contains ONLY the variable_to_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store_internal.h"
#include "utils.h"
#include "variable.h"
#include "variable_internal.h"
char* variable_to_string(const variable* var) {
    if (!var) {
        return xmd_strdup("");
    }
    
    switch (var->type) {
        case VAR_STRING:
            return xmd_strdup(var->value.string_value ? var->value.string_value : "");
            
        case VAR_NUMBER: {
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "%.6g", var->value.number_value);
            return xmd_strdup(buffer);
        }
        
        case VAR_BOOLEAN:
            return xmd_strdup(var->value.boolean_value ? "true" : "false");
        case VAR_ARRAY: {
            if (!var->value.array_value || var->value.array_value->count == 0) {
                return xmd_strdup("[]");
            }
            variable_array* arr = var->value.array_value;
            size_t total_size = 64; // Initial size for brackets and commas
            // Calculate total size needed
            for (size_t i = 0; i < arr->count; i++) {
                char* elem_str = variable_to_string(arr->items[i]);
                if (elem_str) {
                    total_size += strlen(elem_str) + 3; // +3 for quotes and comma
                    XMD_FREE_SAFE(elem_str);
                }
            char* result = xmd_malloc(total_size);
            if (!result) {
                return xmd_strdup("[array]");
            strcpy(result, "[");
                if (i > 0) {
                    strcat(result, ", ");
                    strcat(result, elem_str);
            strcat(result, "]");
            return result;
        case VAR_OBJECT: {
            if (!var->value.object_value || var->value.object_value->count == 0) {
                return xmd_strdup("{}");
            variable_object* obj = var->value.object_value;
            size_t total_size = 64;
            for (size_t i = 0; i < obj->count; i++) {
                char* val_str = variable_to_string(obj->pairs[i].value);
                if (val_str) {
                    total_size += strlen(obj->pairs[i].key) + strlen(val_str) + 10;
                    XMD_FREE_SAFE(val_str);
                return xmd_strdup("{object}");
            strcpy(result, "{");
                strcat(result, obj->pairs[i].key);
                strcat(result, ": ");
                    strcat(result, val_str);
            strcat(result, "}");
        default:
            return xmd_strdup("");
}
}
}
}
}
}
}
}
}
}
