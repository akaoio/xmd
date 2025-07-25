/**
 * @file variable_extended.c
 * @brief Extended variable system implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "variable.h"

/**
 * @brief Array structure for variable arrays
 */
typedef struct {
    variable** items;    /**< Array of variable pointers */
    size_t count;        /**< Number of items */
    size_t capacity;     /**< Array capacity */
} variable_array;

/**
 * @brief Object entry for key-value pairs
 */
typedef struct object_entry {
    char* key;                    /**< Property key */
    variable* value;              /**< Property value */
    struct object_entry* next;    /**< Next entry (linked list) */
} object_entry;

/**
 * @brief Object structure for variable objects
 */
typedef struct {
    object_entry* entries;        /**< Linked list of entries */
    size_t count;                 /**< Number of properties */
} variable_object;

/**
 * @brief Get boolean value directly (convenience function)
 * @param var Variable to get boolean from
 * @return Boolean value or false if not boolean
 */
bool variable_get_boolean(const variable* var) {
    if (!var || var->type != VAR_BOOLEAN) {
        return false;
    }
    return var->value.boolean_value;
}

/**
 * @brief Get number value directly (convenience function)
 * @param var Variable to get number from
 * @return Number value or 0.0 if not number
 */
double variable_get_number(const variable* var) {
    if (!var || var->type != VAR_NUMBER) {
        return 0.0;
    }
    return var->value.number_value;
}

/**
 * @brief Get string value directly (convenience function)
 * @param var Variable to get string from
 * @return String value or NULL if not string
 */
const char* variable_get_string(const variable* var) {
    if (!var || var->type != VAR_STRING) {
        return NULL;
    }
    return var->value.string_value;
}

/**
 * @brief Create array with initial items
 * @param items Array of variable pointers
 * @param count Number of items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count) {
    variable* var = malloc(sizeof(variable));
    if (!var) {
        return NULL;
    }
    
    variable_array* array = malloc(sizeof(variable_array));
    if (!array) {
        free(var);
        return NULL;
    }
    
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
    
    if (count > 0 && items) {
        array->items = malloc(sizeof(variable*) * count);
        if (!array->items) {
            free(array);
            free(var);
            return NULL;
        }
        
        array->capacity = count;
        array->count = count;
        
        for (size_t i = 0; i < count; i++) {
            array->items[i] = variable_ref(items[i]);
        }
    }
    
    var->type = VAR_ARRAY;
    var->value.array_value = array;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Get array length
 * @param var Array variable
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var) {
    if (!var || var->type != VAR_ARRAY || !var->value.array_value) {
        return 0;
    }
    
    variable_array* array = (variable_array*)var->value.array_value;
    return array->count;
}

/**
 * @brief Get array element
 * @param var Array variable
 * @param index Element index
 * @return Element variable or NULL if out of bounds
 */
variable* variable_array_get(const variable* var, size_t index) {
    if (!var || var->type != VAR_ARRAY || !var->value.array_value) {
        return NULL;
    }
    
    variable_array* array = (variable_array*)var->value.array_value;
    if (index >= array->count) {
        return NULL;
    }
    
    return array->items[index];
}

/**
 * @brief Set object property
 * @param var Object variable
 * @param key Property key
 * @param value Property value
 */
void variable_object_set(variable* var, const char* key, variable* value) {
    if (!var || var->type != VAR_OBJECT || !key || !value) {
        return;
    }
    
    variable_object* obj = (variable_object*)var->value.object_value;
    if (!obj) {
        // Initialize object if it doesn't exist
        obj = malloc(sizeof(variable_object));
        if (!obj) {
            return;
        }
        obj->entries = NULL;
        obj->count = 0;
        var->value.object_value = obj;
    }
    
    // Look for existing entry
    for (object_entry* entry = obj->entries; entry; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            // Update existing entry
            variable_unref(entry->value);
            entry->value = variable_ref(value);
            return;
        }
    }
    
    // Create new entry
    object_entry* new_entry = malloc(sizeof(object_entry));
    if (!new_entry) {
        return;
    }
    
    new_entry->key = strdup(key);
    new_entry->value = variable_ref(value);
    new_entry->next = obj->entries;
    obj->entries = new_entry;
    obj->count++;
}

/**
 * @brief Get object property
 * @param var Object variable
 * @param key Property key
 * @return Property value or NULL if not found
 */
variable* variable_object_get(const variable* var, const char* key) {
    if (!var || var->type != VAR_OBJECT || !key || !var->value.object_value) {
        return NULL;
    }
    
    variable_object* obj = (variable_object*)var->value.object_value;
    
    for (object_entry* entry = obj->entries; entry; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
    }
    
    return NULL;
}

/**
 * @brief Free array structure
 * @param array Array to free
 */
void variable_array_free(variable_array* array) {
    if (!array) {
        return;
    }
    
    for (size_t i = 0; i < array->count; i++) {
        variable_unref(array->items[i]);
    }
    
    free(array->items);
    free(array);
}

/**
 * @brief Free object structure
 * @param obj Object to free
 */
void variable_object_free(variable_object* obj) {
    if (!obj) {
        return;
    }
    
    object_entry* entry = obj->entries;
    while (entry) {
        object_entry* next = entry->next;
        free(entry->key);
        variable_unref(entry->value);
        free(entry);
        entry = next;
    }
    
    free(obj);
}