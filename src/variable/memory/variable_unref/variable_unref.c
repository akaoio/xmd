/**
 * @file variable_unref.c
 * @brief Implementation of variable_unref function
 * 
 * This file contains ONLY the variable_unref function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Decrement reference count and free if zero
 * @param var Variable to unreference
 */
void variable_unref(variable* var) {
    if (var == NULL) {
        return;
    }
    
    if (var->ref_count > 0) {
        var->ref_count--;
    }
    
    if (var->ref_count == 0) {
        // Clean up based on type using XMD_VARIABLE_TYPE_DISPATCH
        XMD_VARIABLE_TYPE_DISPATCH(var,
            // VAR_STRING case
            XMD_FREE_SAFE(var->value.string_value),
            
            // VAR_NUMBER case - no cleanup needed
            ((void)0),
            
            // VAR_BOOLEAN case - no cleanup needed
            ((void)0),
            
            // VAR_ARRAY case
            {
                if (var->value.array_value) {
                    for (size_t i = 0; i < var->value.array_value->count; i++) {
                        variable_unref(var->value.array_value->items[i]);
                    }
                    XMD_FREE_SAFE(var->value.array_value->items);
                    XMD_FREE_SAFE(var->value.array_value);
                }
            },
            
            // VAR_OBJECT case
            {
                if (var->value.object_value) {
                    for (size_t i = 0; i < var->value.object_value->count; i++) {
                        XMD_FREE_SAFE(var->value.object_value->pairs[i].key);
                        variable_unref(var->value.object_value->pairs[i].value);
                    }
                    XMD_FREE_SAFE(var->value.object_value->pairs);
                    XMD_FREE_SAFE(var->value.object_value);
                }
            },
            
            // VAR_NULL case - no cleanup needed
            ((void)0),
            
            // default case - no cleanup needed
            ((void)0)
        );
        
        XMD_FREE_SAFE(var);
    }
}
