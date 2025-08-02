/**
 * @file variable_object_set.h
 * @brief Declaration for variable_object_set function
 * 
 * This file contains ONLY the variable_object_set declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_SET_H
#define VARIABLE_OBJECT_SET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_object_set(variable* object_var, const char* key, variable* value);

#endif /* VARIABLE_OBJECT_SET_H */
