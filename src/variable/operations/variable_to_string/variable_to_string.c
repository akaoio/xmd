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
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

char* variable_to_string(const variable* var) {
    if (!var) return xmd_strdup("");
    
    char* result = NULL;
    
    XMD_VARIABLE_TYPE_DISPATCH(var,
        /* VAR_STRING */ 
        result = xmd_strdup(var->value.string_value ? var->value.string_value : ""),
        
        /* VAR_NUMBER */ 
        {
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "%.6g", var->value.number_value);
            result = xmd_strdup(buffer);
        },
        
        /* VAR_BOOLEAN */ 
        result = xmd_strdup(var->value.boolean_value ? "true" : "false"),
        
        /* VAR_ARRAY */ 
        {
            if (!var->value.array_value || var->value.array_value->count == 0) {
                result = xmd_strdup("[]");
            } else {
                result = xmd_strdup("[array]"); // Simplified for now
            }
        },
        
        /* VAR_OBJECT */ 
        {
            if (!var->value.object_value || var->value.object_value->count == 0) {
                result = xmd_strdup("{}");
            } else {
                result = xmd_strdup("{object}"); // Simplified for now
            }
        },
        
        /* VAR_NULL */ 
        result = xmd_strdup(""),
        
        /* default */ 
        result = xmd_strdup("")
    );
    
    return result;
}
