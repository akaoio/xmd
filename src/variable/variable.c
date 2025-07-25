/**
 * @file variable.c
 * @brief Variable system implementation
 * @author XMD Team
 *
 * Implementation of variable creation, reference counting, type conversions,
 * and basic operations for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "variable.h"
#include "../../include/utils.h"

/* Forward declarations for extended functionality */
static void variable_array_free(variable_array* array);
static void variable_object_free(variable_object* obj);

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NULL;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new boolean variable
 * @param value Boolean value
 * @return New boolean variable or NULL on failure
 */
variable* variable_create_boolean(bool value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_BOOLEAN;
    var->value.boolean_value = value;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new number variable
 * @param value Numeric value
 * @return New number variable or NULL on failure
 */
variable* variable_create_number(double value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NUMBER;
    var->value.number_value = value;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new string variable
 * @param value String value (will be copied)
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_STRING;
    var->ref_count = 1;
    
    if (value == NULL) {
        var->value.string_value = malloc(1);
        if (var->value.string_value == NULL) {
            free(var);
            return NULL;
        }
        var->value.string_value[0] = '\0';
    } else {
        size_t len = strlen(value);
        var->value.string_value = malloc(len + 1);
        if (var->value.string_value == NULL) {
            free(var);
            return NULL;
        }
        strcpy(var->value.string_value, value);
    }
    
    return var;
}

/**
 * @brief Create a new array variable
 * @return New empty array variable or NULL on failure
 */
variable* variable_create_array(void) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_ARRAY;
    var->value.array_value = malloc(sizeof(variable_array));
    if (!var->value.array_value) {
        free(var);
        return NULL;
    }
    
    var->value.array_value->items = NULL;
    var->value.array_value->count = 0;
    var->value.array_value->capacity = 0;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Create a new object variable
 * @return New empty object variable or NULL on failure
 */
variable* variable_create_object(void) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_OBJECT;
    var->value.object_value = malloc(sizeof(variable_object));
    if (!var->value.object_value) {
        free(var);
        return NULL;
    }
    
    var->value.object_value->pairs = NULL;
    var->value.object_value->count = 0;
    var->value.object_value->capacity = 0;
    var->ref_count = 1;
    
    return var;
}

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    var->ref_count++;
    return var;
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

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type or VAR_NULL if var is NULL
 */
variable_type variable_get_type(const variable* var) {
    return var ? var->type : VAR_NULL;
}

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (var == NULL) {
        return false;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return false;
        case VAR_BOOLEAN:
            return var->value.boolean_value;
        case VAR_NUMBER:
            return var->value.number_value != 0.0 && !isnan(var->value.number_value);
        case VAR_STRING:
            return var->value.string_value != NULL && strlen(var->value.string_value) > 0;
        case VAR_ARRAY:
        case VAR_OBJECT:
            return var->value.array_value != NULL || var->value.object_value != NULL;
        default:
            return false;
    }
}

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    return xmd_variable_to_number(var);
}

/**
 * @brief Convert variable to string
 * @param var Variable to convert
 * @return String representation (must be freed)
 */
char* variable_to_string(const variable* var) {
    if (var == NULL) {
        char* result = malloc(5);
        if (result) strcpy(result, "null");
        return result;
    }
    
    switch (var->type) {
        case VAR_NULL: {
            char* result = malloc(5);
            if (result) strcpy(result, "null");
            return result;
        }
        case VAR_BOOLEAN: {
            const char* str = var->value.boolean_value ? "true" : "false";
            char* result = malloc(strlen(str) + 1);
            if (result) strcpy(result, str);
            return result;
        }
        case VAR_NUMBER: {
            double num = var->value.number_value;
            if (isnan(num)) {
                char* result = malloc(4);
                if (result) strcpy(result, "NaN");
                return result;
            } else if (isinf(num)) {
                char* result = malloc(9);
                if (result) strcpy(result, num > 0 ? "Infinity" : "-Infinity");
                return result;
            } else if (num == floor(num) && num >= -2147483648.0 && num <= 2147483647.0) {
                char* result = malloc(32);
                if (result) snprintf(result, 32, "%.0f", num);
                return result;
            } else {
                char* result = malloc(32);
                if (result) snprintf(result, 32, "%.6g", num);
                return result;
            }
        }
        case VAR_STRING: {
            if (var->value.string_value == NULL) {
                char* result = malloc(1);
                if (result) result[0] = '\0';
                return result;
            }
            size_t len = strlen(var->value.string_value);
            char* result = malloc(len + 1);
            if (result) strcpy(result, var->value.string_value);
            return result;
        }
        case VAR_ARRAY: {
            char* result = malloc(3);
            if (result) strcpy(result, "[]");
            return result;
        }
        case VAR_OBJECT: {
            char* result = malloc(3);
            if (result) strcpy(result, "{}");
            return result;
        }
        default: {
            char* result = malloc(8);
            if (result) strcpy(result, "unknown");
            return result;
        }
    }
}

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b) {
    return xmd_variable_equals(a, b);
}

/**
 * @brief Create a deep copy of a variable
 * @param var Variable to copy
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
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
            variable* new_array = variable_create_array();
            if (!new_array || !var->value.array_value) return new_array;
            
            // Deep copy array items
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                variable* item_copy = variable_copy(var->value.array_value->items[i]);
                if (item_copy) {
                    variable_array_add(new_array, item_copy);
                    variable_unref(item_copy); // Release our reference, array holds it
                }
            }
            return new_array;
        }
        case VAR_OBJECT: {
            variable* new_object = variable_create_object();
            if (!new_object || !var->value.object_value) return new_object;
            
            // Deep copy object properties
            for (size_t i = 0; i < var->value.object_value->count; i++) {
                const variable_object_pair* pair = &var->value.object_value->pairs[i];
                variable* value_copy = variable_copy(pair->value);
                if (value_copy) {
                    variable_object_set(new_object, pair->key, value_copy);
                    variable_unref(value_copy); // Release our reference, object holds it
                }
            }
            return new_object;
        }
        default:
            return NULL;
    }
}

/* Array implementation */

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
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    
    // Resize if needed
    if (array->count >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        variable** new_items = realloc(array->items, new_capacity * sizeof(variable*));
        if (!new_items) return false;
        
        array->items = new_items;
        array->capacity = new_capacity;
    }
    
    array->items[array->count++] = variable_ref(item);
    return true;
}

/**
 * @brief Get item from array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @return Item variable or NULL if not found/invalid
 */
variable* variable_array_get(const variable* array_var, size_t index) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return NULL;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) return NULL;
    
    return array->items[index];
}

/**
 * @brief Set item in array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @param item Item to set (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_set(variable* array_var, size_t index, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) return false;
    
    variable_unref(array->items[index]);
    array->items[index] = variable_ref(item);
    return true;
}

/**
 * @brief Get array size
 * @param array_var Array variable
 * @return Array size or 0 if not array/invalid
 */
size_t variable_array_size(const variable* array_var) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return 0;
    }
    
    return array_var->value.array_value->count;
}

/* Object implementation */

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
 * @brief Find pair index by key
 * @param object Object to search
 * @param key Key to find
 * @return Index if found, SIZE_MAX if not found
 */
static size_t variable_object_find_key(const variable_object* object, const char* key) {
    if (!object || !key) return SIZE_MAX;
    
    for (size_t i = 0; i < object->count; i++) {
        if (strcmp(object->pairs[i].key, key) == 0) {
            return i;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Set property in object variable
 * @param object_var Object variable
 * @param key Property key
 * @param value Property value (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_object_set(variable* object_var, const char* key, variable* value) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return false;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t existing_index = variable_object_find_key(object, key);
    
    if (existing_index != SIZE_MAX) {
        // Update existing
        variable_unref(object->pairs[existing_index].value);
        object->pairs[existing_index].value = variable_ref(value);
        return true;
    }
    
    // Add new pair
    if (object->count >= object->capacity) {
        size_t new_capacity = object->capacity == 0 ? 4 : object->capacity * 2;
        variable_object_pair* new_pairs = realloc(object->pairs, new_capacity * sizeof(variable_object_pair));
        if (!new_pairs) return false;
        
        object->pairs = new_pairs;
        object->capacity = new_capacity;
    }
    
    object->pairs[object->count].key = strdup(key);
    if (!object->pairs[object->count].key) return false;
    
    object->pairs[object->count].value = variable_ref(value);
    object->count++;
    return true;
}

/**
 * @brief Get property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return NULL;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t index = variable_object_find_key(object, key);
    
    if (index == SIZE_MAX) return NULL;
    return object->pairs[index].value;
}

/**
 * @brief Remove property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return true if removed, false if not found/invalid
 */
bool variable_object_remove(variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return false;
    }
    
    variable_object* object = object_var->value.object_value;
    size_t index = variable_object_find_key(object, key);
    
    if (index == SIZE_MAX) return false;
    
    // Free the pair
    free(object->pairs[index].key);
    variable_unref(object->pairs[index].value);
    
    // Move last pair to this position
    if (index < object->count - 1) {
        object->pairs[index] = object->pairs[object->count - 1];
    }
    object->count--;
    
    return true;
}

/**
 * @brief Get object property count
 * @param object_var Object variable
 * @return Property count or 0 if not object/invalid
 */
size_t variable_object_size(const variable* object_var) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value) {
        return 0;
    }
    
    return object_var->value.object_value->count;
}

/**
 * @brief Get all object keys
 * @param object_var Object variable
 * @param count Output for key count
 * @return Array of key strings (must be freed) or NULL
 */
char** variable_object_keys(const variable* object_var, size_t* count) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    variable_object* object = object_var->value.object_value;
    *count = object->count;
    
    if (object->count == 0) return NULL;
    
    char** keys = malloc(object->count * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < object->count; i++) {
        keys[i] = strdup(object->pairs[i].key);
        if (!keys[i]) {
            // Cleanup on failure
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            *count = 0;
            return NULL;
        }
    }
    
    return keys;
}

/**
 * @brief Get array length
 * @param var Array variable
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var) {
    return variable_array_size(var);
}

/**
 * @brief Create array with initial items
 * @param items Array of variable pointers
 * @param count Number of items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count) {
    variable* array_var = variable_create_array();
    if (!array_var || !items) {
        return array_var;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (!variable_array_add(array_var, items[i])) {
            variable_unref(array_var);
            return NULL;
        }
    }
    
    return array_var;
}