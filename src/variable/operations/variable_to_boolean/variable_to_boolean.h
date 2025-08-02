/**
 * @file variable_to_boolean.h
 * @brief Declaration for variable_to_boolean function
 * 
 * This file contains ONLY the variable_to_boolean declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_TO_BOOLEAN_H
#define VARIABLE_TO_BOOLEAN_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_to_boolean(const variable* var);

#endif /* VARIABLE_TO_BOOLEAN_H */
