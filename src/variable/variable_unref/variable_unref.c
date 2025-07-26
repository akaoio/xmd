/**
 * @file variable_unref.c
 * @brief Variable system implementation - reference decrement and cleanup
 * @author XMD Team
 *
 * Implementation of variable reference decrement and cleanup for the XMD variable system.
 * Includes static helper functions for array and object cleanup.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/* Forward declarations for extended functionality */
static void variable_array_free(variable_array* array);
static void variable_object_free(variable_object* obj);

/**
 * @brief Free array structure and all its items
 * @param array Array to free
 */
static void variable_array_free(variable_array* array) {
    if (!array) return;
    
    // Unref all items
    for (size_t i = 0; i < array->count; i++) {
        variable_unref(array->items[i]);
    }
    
    free(array->items);
    free(array);
}

/**
 * @brief Free object structure and all its pairs
 * @param object Object to free
 */
static void variable_object_free(variable_object* object) {
    if (!object) return;
    
    // Free all pairs
    for (size_t i = 0; i < object->count; i++) {
        free(object->pairs[i].key);
        variable_unref(object->pairs[i].value);
    }
    
    free(object->pairs);
    free(object);
}

/**
 * @brief Decrement reference count and destroy if zero
 * @param var Variable to unreference (can be NULL)
 */
void variable_unref(variable* var) {
    if (var == NULL) {
        return;
    }
    
    var->ref_count--;
    if (var->ref_count == 0) {
        switch (var->type) {
            case VAR_STRING:
                free(var->value.string_value);
                break;
            case VAR_ARRAY:
                variable_array_free(var->value.array_value);
                break;
            case VAR_OBJECT:
                variable_object_free(var->value.object_value);
                break;
            default:
                break;
        }
        free(var);
    }
}
