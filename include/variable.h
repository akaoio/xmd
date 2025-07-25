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
        void* array_value;        /**< Array structure pointer */
        void* object_value;       /**< Object structure pointer */
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

/**
 * @brief Get array element
 * @param var Array variable
 * @param index Element index
 * @return Element variable or NULL if out of bounds
 */
variable* variable_array_get(const variable* var, size_t index);

/**
 * @brief Set object property
 * @param var Object variable
 * @param key Property key
 * @param value Property value
 */
void variable_object_set(variable* var, const char* key, variable* value);

/**
 * @brief Get object property
 * @param var Object variable
 * @param key Property key
 * @return Property value or NULL if not found
 */
variable* variable_object_get(const variable* var, const char* key);

/* Convenience aliases for consistency */
#define variable_new_null() variable_create_null()
#define variable_new_boolean(x) variable_create_boolean(x)
#define variable_new_number(x) variable_create_number(x)
#define variable_new_string(x) variable_create_string(x)
#define variable_new_object() variable_create_object()

#endif /* VARIABLE_H */