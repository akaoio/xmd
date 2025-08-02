/**
 * @file variable.h
 * @brief Variable system header
 * @author XMD Team
 *
 * Defines variable structure and basic operations for the XMD
 * variable management system with type safety and reference counting.
 */

#ifndef VARIABLE_H
#define VARIABLE_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @enum variable_type
 * @brief Variable type enumeration
 */
typedef enum {
    VAR_NULL,       /**< Null/undefined value */
    VAR_BOOLEAN,    /**< Boolean true/false */
    VAR_NUMBER,     /**< Numeric value (double) */
    VAR_STRING,     /**< String value */
    VAR_ARRAY,      /**< Array of variables */
    VAR_OBJECT,     /**< Object/map of key-value pairs */
    
    /* Aliases for consistency */
    VARIABLE_TYPE_NULL = VAR_NULL,
    VARIABLE_TYPE_BOOLEAN = VAR_BOOLEAN, 
    VARIABLE_TYPE_NUMBER = VAR_NUMBER,
    VARIABLE_TYPE_STRING = VAR_STRING,
    VARIABLE_TYPE_ARRAY = VAR_ARRAY,
    VARIABLE_TYPE_OBJECT = VAR_OBJECT
} variable_type;

/* Forward declarations */
typedef struct variable variable;
typedef struct variable_array variable_array;
typedef struct variable_object variable_object;

/**
 * @struct variable_array
 * @brief Dynamic array of variables
 */
typedef struct variable_array {
    variable** items;        /**< Array of variable pointers */
    size_t count;           /**< Number of items */
    size_t capacity;        /**< Allocated capacity */
} variable_array;

/**
 * @struct variable_object_pair
 * @brief Key-value pair for object
 */
typedef struct variable_object_pair {
    char* key;              /**< Key string (owned) */
    variable* value;        /**< Value variable (reference) */
} variable_object_pair;

/**
 * @struct variable_object
 * @brief Dynamic object/map of key-value pairs
 */
typedef struct variable_object {
    variable_object_pair* pairs;  /**< Array of key-value pairs */
    size_t count;                /**< Number of pairs */
    size_t capacity;             /**< Allocated capacity */
} variable_object;

/**
 * @struct variable
 * @brief Variable representation with type and value
 */
typedef struct variable {
    variable_type type;           /**< Variable type */
    union {
        bool boolean_value;       /**< Boolean value */
        double number_value;      /**< Numeric value */
        char* string_value;       /**< String value (owned) */
        variable_array* array_value;   /**< Array structure pointer */
        variable_object* object_value; /**< Object structure pointer */
    } value;                      /**< Value union */
    size_t ref_count;            /**< Reference count for memory management */
} variable;

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void);

/**
 * @brief Create a new boolean variable
 * @param value Boolean value
 * @return New boolean variable or NULL on failure
 */
variable* variable_create_boolean(bool value);

/**
 * @brief Create a new number variable
 * @param value Numeric value
 * @return New number variable or NULL on failure
 */
variable* variable_create_number(double value);

/**
 * @brief Create a new string variable
 * @param value String value (will be copied)
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value);

/**
 * @brief Create a new array variable
 * @return New empty array variable or NULL on failure
 */
variable* variable_create_array(void);

/**
 * @brief Create a new object variable
 * @return New empty object variable or NULL on failure
 */
variable* variable_create_object(void);

/* Array operations */

/**
 * @brief Add item to array variable
 * @param array_var Array variable
 * @param item Item to add (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_add(variable* array_var, variable* item);

/**
 * @brief Get item from array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @return Item variable or NULL if not found/invalid
 */
variable* variable_array_get(const variable* array_var, size_t index);

/**
 * @brief Set item in array variable by index
 * @param array_var Array variable
 * @param index Item index
 * @param item Item to set (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_array_set(variable* array_var, size_t index, variable* item);

/**
 * @brief Get array size
 * @param array_var Array variable
 * @return Array size or 0 if not array/invalid
 */
size_t variable_array_size(const variable* array_var);

/* Object operations */

/**
 * @brief Set property in object variable
 * @param object_var Object variable
 * @param key Property key
 * @param value Property value (reference will be taken)
 * @return true on success, false on failure
 */
bool variable_object_set(variable* object_var, const char* key, variable* value);

/**
 * @brief Get property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return Property value or NULL if not found/invalid
 */
variable* variable_object_get(const variable* object_var, const char* key);

/**
 * @brief Remove property from object variable
 * @param object_var Object variable
 * @param key Property key
 * @return true if removed, false if not found/invalid
 */
bool variable_object_remove(variable* object_var, const char* key);

/**
 * @brief Get object property count
 * @param object_var Object variable
 * @return Property count or 0 if not object/invalid
 */
size_t variable_object_size(const variable* object_var);

/**
 * @brief Get all object keys
 * @param object_var Object variable
 * @param count Output for key count
 * @return Array of key strings (must be freed) or NULL
 */
char** variable_object_keys(const variable* object_var, size_t* count);

/**
 * @brief Find key index in object variable (internal helper)
 * @param object_var Object variable
 * @param key Key to find
 * @return Key index or SIZE_MAX if not found
 */
size_t variable_object_find_key(const variable* object_var, const char* key);

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var);

/**
 * @brief Decrement reference count and destroy if zero
 * @param var Variable to unreference (can be NULL)
 */
void variable_unref(variable* var);

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type or VAR_NULL if var is NULL
 */
variable_type variable_get_type(const variable* var);

/**
 * @brief Convert variable to boolean
 * @param var Variable to convert
 * @return Boolean representation
 */
bool variable_to_boolean(const variable* var);

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var);

/**
 * @brief Convert variable to string
 * @param var Variable to convert
 * @return String representation (must be freed)
 */
char* variable_to_string(const variable* var);

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b);

/**
 * @brief Create a deep copy of a variable
 * @param var Variable to copy
 * @return Copy of variable or NULL on failure
 */
variable* variable_copy(const variable* var);

/**
 * @brief Get boolean value directly (convenience function)
 * @param var Variable to get boolean from
 * @return Boolean value or false if not boolean
 */
bool variable_get_boolean(const variable* var);

/**
 * @brief Get number value directly (convenience function)
 * @param var Variable to get number from
 * @return Number value or 0.0 if not number
 */
double variable_get_number(const variable* var);

/**
 * @brief Get string value directly (convenience function)
 * @param var Variable to get string from
 * @return String value or NULL if not string
 */
const char* variable_get_string(const variable* var);

/**
 * @brief Create array with initial items
 * @param items Array of variable pointers
 * @param count Number of items
 * @return New array variable or NULL on failure
 */
variable* variable_new_array(variable** items, size_t count);

/**
 * @brief Get array length
 * @param var Array variable
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var);

/* variable_array_get is declared above */


/* Convenience aliases for consistency */
#define variable_new_null() variable_create_null()
#define variable_new_boolean(x) variable_create_boolean(x)
#define variable_new_number(x) variable_create_number(x)
#define variable_new_string(x) variable_create_string(x)
#define variable_new_object() variable_create_object()

#endif /* VARIABLE_H */
