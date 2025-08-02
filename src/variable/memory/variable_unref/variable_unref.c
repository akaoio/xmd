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
        // Clean up based on type
        switch (var->type) {
            case VAR_STRING:
                free(var->value.string_value);
                break;
                
            case VAR_ARRAY:
                if (var->value.array_value) {
                    for (size_t i = 0; i < var->value.array_value->count; i++) {
                        variable_unref(var->value.array_value->items[i]);
                    }
                    free(var->value.array_value->items);
                    free(var->value.array_value);
                }
                break;
                
            case VAR_OBJECT:
                if (var->value.object_value) {
                    for (size_t i = 0; i < var->value.object_value->count; i++) {
                        free(var->value.object_value->pairs[i].key);
                        variable_unref(var->value.object_value->pairs[i].value);
                    }
                    free(var->value.object_value->pairs);
                    free(var->value.object_value);
                }
                break;
                
            default:
                // No cleanup needed for NULL, BOOLEAN, NUMBER
                break;
        }
        
        free(var);
    }
}
