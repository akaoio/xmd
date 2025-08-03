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
#include "../../../../include/utils.h"
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../utils/common/common_macros.h"

char* variable_to_string(const variable* var) {
    XMD_VALIDATE_PTRS(xmd_strdup(""), var);
    
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
            return xmd_strdup("[array]"); // Simplified for now
        }
        
        case VAR_OBJECT: {
            if (!var->value.object_value || var->value.object_value->count == 0) {
                return xmd_strdup("{}");
            }
            return xmd_strdup("{object}"); // Simplified for now
        }
        
        default:
            return xmd_strdup("");
    }
}
