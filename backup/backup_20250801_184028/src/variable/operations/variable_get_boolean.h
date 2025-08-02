/**
 * @file variable_get_boolean.h
 * @brief Declaration for variable_get_boolean function
 * 
 * This file contains ONLY the variable_get_boolean declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_GET_BOOLEAN_H
#define VARIABLE_GET_BOOLEAN_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_get_boolean(const variable* var);

#endif /* VARIABLE_GET_BOOLEAN_H */
