/**
 * @file variable.c
 * @brief Consolidated variable system implementation
 * @author XMD Team
 *
 * Complete implementation of the XMD variable system with type safety,
 * reference counting, and support for all basic data types including
 * arrays and objects. This consolidates all variable operations into
 * a single file for better maintainability and performance.
 */

#define _GNU_SOURCE  // For strdup - must be before includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include "../include/variable_internal.h"
#include "../include/utils.h"

/* ============================================================================
 * VARIABLE CREATION FUNCTIONS
 * ============================================================================ */

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    variable* var = xmd_malloc(sizeof(variable));
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
    variable* var = xmd_malloc(sizeof(variable));
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
    variable* var = xmd_malloc(sizeof(variable));
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
    variable* var = xmd_malloc(sizeof(variable));
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
    variable* var = xmd_malloc(sizeof(variable));
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
    variable* var = xmd_malloc(sizeof(variable));
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

/* ============================================================================
 * REFERENCE COUNTING FUNCTIONS
 * ============================================================================ */

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
    if (!var) {
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

/* ============================================================================
 * TYPE CONVERSION FUNCTIONS
 * ============================================================================ */

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type
 */
variable_type variable_get_type(const variable* var) {
    if (!var) {
        return VAR_NULL;
    }
    
    return var->type;
}

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var) {
    if (!var) {
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
            return var->value.string_value && strlen(var->value.string_value) > 0;
            
        case VAR_ARRAY:
            return var->value.array_value && var->value.array_value->count > 0;
            
        case VAR_OBJECT:
            return var->value.object_value && var->value.object_value->count > 0;
    }
    
    return false;
}

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    if (!var) {
        return 0.0;
    }
    
    switch (var->type) {
        case VAR_NULL:
            return 0.0;
            
        case VAR_BOOLEAN:
            return var->value.boolean_value ? 1.0 : 0.0;
            
        case VAR_NUMBER:
            return var->value.number_value;
            
        case VAR_STRING:
            if (!var->value.string_value) return 0.0;
            
            char* endptr;
            double result = strtod(var->value.string_value, &endptr);
            
            // If conversion failed or there are remaining characters
            if (endptr == var->value.string_value || *endptr != '\0') {
                return 0.0;
            }
            
            return result;
            
        case VAR_ARRAY:
            return var->value.array_value ? (double)var->value.array_value->count : 0.0;
            
        case VAR_OBJECT:
            return var->value.object_value ? (double)var->value.object_value->count : 0.0;
    }
    
    return 0.0;
}

/**
 * @brief Convert variable to string
 * @param var Variable to convert
 * @return String representation (must be freed)
 */
char* variable_to_string(const variable* var) {
    if (var == NULL) {
        char* result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }
    
    switch (var->type) {
        case VAR_NULL: {
            char* result = malloc(5);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, "null");
            return result;
        }
        case VAR_BOOLEAN: {
            if (var->value.boolean_value) {
                char* result = malloc(5);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, "true");
                return result;
            } else {
                char* result = malloc(6);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, "false");
                return result;
            }
        }
        case VAR_NUMBER: {
            // Convert number to string
            char buffer[64];
            double num = var->value.number_value;
            
            if (isnan(num)) {
                strcpy(buffer, "NaN");
            } else if (isinf(num)) {
                if (num > 0) {
                    strcpy(buffer, "Infinity");
                } else {
                    strcpy(buffer, "-Infinity");
                }
            } else if (floor(num) == num && num >= -2147483648.0 && num <= 2147483647.0) {
                // Integer representation
                snprintf(buffer, sizeof(buffer), "%.0f", num);
            } else {
                // Floating point representation
                snprintf(buffer, sizeof(buffer), "%.15g", num);
            }
            
            size_t len = strlen(buffer);
            char* result = malloc(len + 1);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, buffer);
            return result;
        }
        case VAR_STRING: {
            if (var->value.string_value == NULL) {
                char* result = malloc(1);
                if (result == NULL) {
                    return NULL;
                }
                result[0] = '\0';
                return result;
            }
            
            size_t len = strlen(var->value.string_value);
            char* result = malloc(len + 1);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, var->value.string_value);
            return result;
        }
        case VAR_ARRAY: {
            // Join array elements into string
            if (var->value.array_value == NULL || var->value.array_value->count == 0) {
                char* result = malloc(1);
                if (result == NULL) {
                    return NULL;
                }
                result[0] = '\0';
                return result;
            }
            
            // First pass: calculate total length needed
            size_t total_len = 0;
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                variable* elem = var->value.array_value->items[i];
                char* elem_str = variable_to_string(elem);
                if (elem_str) {
                    total_len += strlen(elem_str);
                    free(elem_str);
                }
                if (i < var->value.array_value->count - 1) {
                    total_len += 2; // ", "
                }
            }
            
            // Allocate result buffer
            char* result = malloc(total_len + 1);
            if (result == NULL) {
                return NULL;
            }
            result[0] = '\0';
            
            // Second pass: build the string
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                variable* elem = var->value.array_value->items[i];
                char* elem_str = variable_to_string(elem);
                if (elem_str) {
                    strcat(result, elem_str);
                    free(elem_str);
                }
                if (i < var->value.array_value->count - 1) {
                    strcat(result, ", ");
                }
            }
            
            return result;
        }
        case VAR_OBJECT: {
            // Simple object representation for now
            char* result = malloc(9);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, "[object]");
            return result;
        }
    }
    
    return NULL;
}

/**
 * @brief Convert variable to different type
 * @param var Variable to convert
 * @param target_type Target type
 * @return Converted variable or NULL on error
 */
variable* variable_convert(variable* var, variable_type target_type) {
    if (!var) {
        return NULL;
    }
    
    // If already the target type, return a reference
    if (var->type == target_type) {
        return variable_ref(var);
    }
    
    switch (target_type) {
        case VAR_BOOLEAN:
            return variable_create_boolean(variable_to_boolean(var));
            
        case VAR_NUMBER:
            return variable_create_number(variable_to_number(var));
            
        case VAR_STRING: {
            char* str = variable_to_string(var);
            if (!str) return NULL;
            variable* result = variable_create_string(str);
            free(str);
            return result;
        }
        
        case VAR_NULL:
            return variable_create_null();
            
        default:
            return NULL; // Cannot convert to array/object types
    }
}

/* ============================================================================
 * ARRAY OPERATIONS
 * ============================================================================ */

/**
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value || !item) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    
    // Resize if needed
    if (array->count >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        variable** new_items = xmd_realloc(array->items, new_capacity * sizeof(variable*));
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
    if (index >= array->count) {
        return NULL;
    }
    
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
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value || !item) {
        return false;
    }
    
    variable_array* array = array_var->value.array_value;
    if (index >= array->count) {
        return false;
    }
    
    // Unreference old item and set new one
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

/**
 * @brief Get array length (alias for size)
 * @param var Array variable
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var) {
    return variable_array_size(var);
}

/**
 * @brief Free array contents (internal helper)
 * @param array_var Array variable
 */
void variable_array_free(variable* array_var) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return;
    }
    
    variable_array* array = array_var->value.array_value;
    for (size_t i = 0; i < array->count; i++) {
        variable_unref(array->items[i]);
    }
    
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}

/**
 * @brief Create array with initial items
 * @param items Array of variable pointers
 * @param count Number of items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count) {
    variable* array_var = variable_create_array();
    if (!array_var) {
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (!variable_array_add(array_var, items[i])) {
            variable_unref(array_var);
            return NULL;
        }
    }
    
    return array_var;
}

/* ============================================================================
 * OBJECT OPERATIONS
 * ============================================================================ */

/**
 * @brief Find key index in object variable (internal helper)
 * @param object_var Object variable
 * @param key Key to find
 * @return Key index or SIZE_MAX if not found
 */
size_t variable_object_find_key(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value || !key) {
        return SIZE_MAX;
    }
    
    variable_object* obj = object_var->value.object_value;
    for (size_t i = 0; i < obj->count; i++) {
        if (strcmp(obj->pairs[i].key, key) == 0) {
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
    if (!object_var || object_var->type != VAR_OBJECT || !key || !value) {
        return false;
    }
    
    variable_object* obj = object_var->value.object_value;
    if (!obj) {
        return false;
    }
    
    // Check if key already exists
    size_t existing_index = variable_object_find_key(object_var, key);
    if (existing_index != SIZE_MAX) {
        // Update existing value
        variable_unref(obj->pairs[existing_index].value);
        obj->pairs[existing_index].value = variable_ref(value);
        return true;
    }
    
    // Add new key-value pair
    if (obj->count >= obj->capacity) {
        size_t new_capacity = obj->capacity == 0 ? 8 : obj->capacity * 2;
        variable_object_pair* new_pairs = xmd_realloc(obj->pairs, 
                                                 new_capacity * sizeof(variable_object_pair));
        if (!new_pairs) {
            return false;
        }
        obj->pairs = new_pairs;
        obj->capacity = new_capacity;
    }
    
    obj->pairs[obj->count].key = strdup(key);
    if (!obj->pairs[obj->count].key) {
        return false;
    }
    
    obj->pairs[obj->count].value = variable_ref(value);
    obj->count++;
    
    return true;
}

/**
 * @brief Get property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !key) {
        return NULL;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    if (index == SIZE_MAX) {
        return NULL;
    }
    
    return object_var->value.object_value->pairs[index].value;
}

/**
 * @brief Remove property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return true if removed, false if not found/invalid
 */
bool variable_object_remove(variable* object_var, const char* key) {
    if (!object_var || object_var->type != VAR_OBJECT || !key) {
        return false;
    }
    
    variable_object* obj = object_var->value.object_value;
    if (!obj) {
        return false;
    }
    
    size_t index = variable_object_find_key(object_var, key);
    if (index == SIZE_MAX) {
        return false;
    }
    
    // Free the key and unreference the value
    free(obj->pairs[index].key);
    variable_unref(obj->pairs[index].value);
    
    // Shift remaining pairs down
    for (size_t i = index; i < obj->count - 1; i++) {
        obj->pairs[i] = obj->pairs[i + 1];
    }
    
    obj->count--;
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
    
    variable_object* obj = object_var->value.object_value;
    *count = obj->count;
    
    if (obj->count == 0) {
        return NULL;
    }
    
    char** keys = malloc(obj->count * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < obj->count; i++) {
        keys[i] = strdup(obj->pairs[i].key);
        if (!keys[i]) {
            // Free previously allocated keys on failure
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

/*
 * @brief Convert variable to string representation
 * @param var Variable to convert
 * @return String representation (must be freed by caller)
 * DUPLICATE FUNCTION - COMMENTED OUT
 */
#if 0
char* variable_to_string(const variable* var) {
    if (!var) {
        return xmd_strdup("");
    }
    
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
            
            variable_array* arr = var->value.array_value;
            size_t total_size = 64; // Initial size for brackets and commas
            
            // Calculate total size needed
            for (size_t i = 0; i < arr->count; i++) {
                char* elem_str = variable_to_string(arr->items[i]);
                if (elem_str) {
                    total_size += strlen(elem_str) + 3; // +3 for quotes and comma
                    free(elem_str);
                }
            }
            
            char* result = xmd_malloc(total_size);
            if (!result) {
                return xmd_strdup("[array]");
            }
            
            strcpy(result, "[");
            for (size_t i = 0; i < arr->count; i++) {
                if (i > 0) {
                    strcat(result, ", ");
                }
                char* elem_str = variable_to_string(arr->items[i]);
                if (elem_str) {
                    strcat(result, elem_str);
                    free(elem_str);
                }
            }
            strcat(result, "]");
            return result;
        }
        
        case VAR_OBJECT: {
            if (!var->value.object_value || var->value.object_value->count == 0) {
                return xmd_strdup("{}");
            }
            
            variable_object* obj = var->value.object_value;
            size_t total_size = 64;
            
            // Calculate total size needed
            for (size_t i = 0; i < obj->count; i++) {
                char* val_str = variable_to_string(obj->pairs[i].value);
                if (val_str) {
                    total_size += strlen(obj->pairs[i].key) + strlen(val_str) + 10;
                    free(val_str);
                }
            }
            
            char* result = xmd_malloc(total_size);
            if (!result) {
                return xmd_strdup("{object}");
            }
            
            strcpy(result, "{");
            for (size_t i = 0; i < obj->count; i++) {
                if (i > 0) {
                    strcat(result, ", ");
                }
                strcat(result, obj->pairs[i].key);
                strcat(result, ": ");
                char* val_str = variable_to_string(obj->pairs[i].value);
                if (val_str) {
                    strcat(result, val_str);
                    free(val_str);
                }
            }
            strcat(result, "}");
            return result;
        }
        
        default:
            return xmd_strdup("");
    }
}
#endif // 0

/**
 * @brief Free object contents (internal helper)
 * @param object_var Object variable
 */
void variable_object_free(variable* object_var) {
    if (!object_var || object_var->type != VAR_OBJECT || !object_var->value.object_value) {
        return;
    }
    
    variable_object* obj = object_var->value.object_value;
    for (size_t i = 0; i < obj->count; i++) {
        free(obj->pairs[i].key);
        variable_unref(obj->pairs[i].value);
    }
    
    free(obj->pairs);
    obj->pairs = NULL;
    obj->count = 0;
    obj->capacity = 0;
}

/* ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================ */

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

/**
 * @brief Create a deep copy of a variable
 * @param var Variable to copy
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var) {
    if (!var) {
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
            variable* copy = variable_create_array();
            if (!copy) return NULL;
            
            if (var->value.array_value) {
                for (size_t i = 0; i < var->value.array_value->count; i++) {
                    variable* item_copy = variable_copy(var->value.array_value->items[i]);
                    if (!item_copy || !variable_array_add(copy, item_copy)) {
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
            if (!copy) return NULL;
            
            if (var->value.object_value) {
                for (size_t i = 0; i < var->value.object_value->count; i++) {
                    const char* key = var->value.object_value->pairs[i].key;
                    variable* value_copy = variable_copy(var->value.object_value->pairs[i].value);
                    if (!value_copy || !variable_object_set(copy, key, value_copy)) {
                        variable_unref(value_copy);
                        variable_unref(copy);
                        return NULL;
                    }
                    variable_unref(value_copy); // object_set takes a reference
                }
            }
            return copy;
        }
    }
    
    return NULL;
}

/* ============================================================================
 * CONVENIENCE GET FUNCTIONS
 * ============================================================================ */

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

/* ============================================================================
 * EXTENDED FUNCTIONALITY
 * ============================================================================ */

/**
 * @brief Extended variable functionality placeholder
 * @param var Variable for extended operations
 * @return Success status
 *
 * This function serves as a placeholder for any extended variable
 * functionality that may be needed in the future.
 */
bool variable_extended(variable* var) {
    if (!var) {
        return false;
    }
    
    // Extended functionality would be implemented here
    return true;
}
