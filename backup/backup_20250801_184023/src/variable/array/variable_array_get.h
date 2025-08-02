/**
 * @file variable_array_get.h
 * @brief Declaration for variable_array_get function
 * 
 * This file contains ONLY the variable_array_get declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_ARRAY_GET_H
#define VARIABLE_ARRAY_GET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_array_get(const variable* array_var, size_t index);

#endif /* VARIABLE_ARRAY_GET_H */
