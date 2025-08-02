/**
 * @file variable_object_remove.h
 * @brief Declaration for variable_object_remove function
 * 
 * This file contains ONLY the variable_object_remove declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_REMOVE_H
#define VARIABLE_OBJECT_REMOVE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_object_remove(variable* object_var, const char* key);

#endif /* VARIABLE_OBJECT_REMOVE_H */
