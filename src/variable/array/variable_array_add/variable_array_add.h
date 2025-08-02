/**
 * @file variable_array_add.h
 * @brief Declaration for variable_array_add function
 * 
 * This file contains ONLY the variable_array_add declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_ARRAY_ADD_H
#define VARIABLE_ARRAY_ADD_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_array_add(variable* array_var, variable* item);

#endif /* VARIABLE_ARRAY_ADD_H */
