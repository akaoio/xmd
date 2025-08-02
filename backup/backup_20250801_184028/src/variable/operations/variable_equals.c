/**
 * @file variable_equals.c
 * @brief Implementation of variable_equals function
 * 
 * This file contains ONLY the variable_equals function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdbool.h>
#include <string.h>

#include "store_internal.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b) {
    if (a == b) {
        return true;
    }
    
    if (!a || !b) {
        return false;
    }
    
    if (a->type != b->type) {
        return false;
    }
    
    switch (a->type) {
        case VAR_NULL:
            return true;
            
        case VAR_BOOLEAN:
            return a->value.boolean_value == b->value.boolean_value;
            
        case VAR_NUMBER:
            return a->value.number_value == b->value.number_value;
            
        case VAR_STRING:
            if (!a->value.string_value && !b->value.string_value) {
                return true;
            }
            if (!a->value.string_value || !b->value.string_value) {
                return false;
            }
            return strcmp(a->value.string_value, b->value.string_value) == 0;
            
        case VAR_ARRAY:
            if (!a->value.array_value && !b->value.array_value) {
                return true;
            }
            if (!a->value.array_value || !b->value.array_value) {
                return false;
            }
            if (a->value.array_value->count != b->value.array_value->count) {
                return false;
            }
            for (size_t i = 0; i < a->value.array_value->count; i++) {
                if (!variable_equals(a->value.array_value->items[i], 
                                   b->value.array_value->items[i])) {
                    return false;
                }
            }
            return true;
            
        case VAR_OBJECT:
            if (!a->value.object_value && !b->value.object_value) {
                return true;
            }
            if (!a->value.object_value || !b->value.object_value) {
                return false;
            }
            if (a->value.object_value->count != b->value.object_value->count) {
                return false;
            }
            
            // Check that all keys in a exist in b with equal values
            for (size_t i = 0; i < a->value.object_value->count; i++) {
                const char* key = a->value.object_value->pairs[i].key;
                variable* a_val = a->value.object_value->pairs[i].value;
                variable* b_val = variable_object_get(b, key);
                if (!variable_equals(a_val, b_val)) {
                    return false;
                }
            }
            return true;
    }
    
    return false;
}