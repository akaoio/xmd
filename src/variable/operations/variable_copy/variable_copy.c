
/**
 * @file variable_copy.c
 * @brief Implementation of variable_copy function
 * 
 * This file contains ONLY the variable_copy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create a deep copy of a variable
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    XMD_VALIDATE_PTR_RETURN(var, NULL);
    
    variable* result = NULL;
    
    XMD_VARIABLE_TYPE_DISPATCH(var,
        /* VAR_STRING */
        result = variable_create_string(var->value.string_value),
        
        /* VAR_NUMBER */
        result = variable_create_number(var->value.number_value),
        
        /* VAR_BOOLEAN */
        result = variable_create_boolean(var->value.boolean_value),
        
        /* VAR_ARRAY */
        {
            result = variable_create_array();
            if (result && var->value.array_value) {
                for (size_t i = 0; i < var->value.array_value->count; i++) {
                    variable* item_copy = variable_copy(var->value.array_value->items[i]);
                    if (!item_copy || !variable_array_add(result, item_copy)) {
                        printf("[ERROR] variable_copy: Failed to copy array item %zu\n", i);
                        variable_unref(item_copy);
                        variable_unref(result);
                        result = NULL;
                        break;
                    }
                    variable_unref(item_copy); // array_add takes a reference
                }
            }
        },
        
        /* VAR_OBJECT */
        {
            result = variable_create_object();
            if (result && var->value.object_value) {
                for (size_t i = 0; i < var->value.object_value->count; i++) {
                    const char* key = var->value.object_value->pairs[i].key;
                    variable* value_copy = variable_copy(var->value.object_value->pairs[i].value);
                    if (!value_copy || !variable_object_set(result, key, value_copy)) {
                        printf("[ERROR] variable_copy: Failed to copy object property '%s'\n", key);
                        variable_unref(value_copy);
                        variable_unref(result);
                        result = NULL;
                        break;
                    }
                    variable_unref(value_copy); // object_set takes a reference
                }
            }
        },
        
        /* VAR_NULL */
        result = variable_create_null(),
        
        /* default */
        {
            printf("[ERROR] variable_copy: Unknown variable type %d\n", var->type);
            result = NULL;
        }
    );
    
    return result;
}
