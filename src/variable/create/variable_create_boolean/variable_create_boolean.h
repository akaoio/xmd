/**
 * @file variable_create_boolean.h
 * @brief Declaration for variable_create_boolean function
 * 
 * This file contains ONLY the variable_create_boolean declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_BOOLEAN_H
#define VARIABLE_CREATE_BOOLEAN_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_boolean(bool value);

#endif /* VARIABLE_CREATE_BOOLEAN_H */
