
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

/**
 * @brief Create a deep copy of a variable
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    XMD_NULL_CHECK(var, NULL);
    
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
            variable* copy = variable_create_array();
            XMD_NULL_CHECK(copy, NULL);
            if (var->value.array_value) {
                for (size_t i = 0; i < var->value.array_value->count; i++) {
                    variable* item_copy = variable_copy(var->value.array_value->items[i]);
                    if (!item_copy || !variable_array_add(copy, item_copy)) {
                        printf("[ERROR] variable_copy: Failed to copy array item %zu\n", i);
                        variable_unref(item_copy);
                        variable_unref(copy);
                        return NULL;
                    }
                    variable_unref(item_copy); // array_add takes a reference
                }
            }
            return copy;
        }
        
        case VAR_OBJECT: {
            variable* copy = variable_create_object();
            XMD_NULL_CHECK(copy, NULL);
            if (var->value.object_value) {
                for (size_t i = 0; i < var->value.object_value->count; i++) {
                    const char* key = var->value.object_value->pairs[i].key;
                    variable* value_copy = variable_copy(var->value.object_value->pairs[i].value);
                    if (!value_copy || !variable_object_set(copy, key, value_copy)) {
                        XMD_ERROR_RETURN(NULL, "variable_copy: Failed to copy object property '%s'", key);
                        variable_unref(value_copy);
                        variable_unref(copy);
                        return NULL;
                    }
                    variable_unref(value_copy); // object_set takes a reference
                }
            }
            return copy;
        }
        
        default:
            XMD_ERROR_RETURN(NULL, "variable_copy: Unknown variable type %d", var->type);
    }
}
