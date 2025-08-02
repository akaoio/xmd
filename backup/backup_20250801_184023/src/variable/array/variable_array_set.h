/**
 * @file variable_array_set.h
 * @brief Declaration for variable_array_set function
 * 
 * This file contains ONLY the variable_array_set declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_ARRAY_SET_H
#define VARIABLE_ARRAY_SET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_array_set(variable* array_var, size_t index, variable* item);

#endif /* VARIABLE_ARRAY_SET_H */
