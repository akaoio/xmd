/**
 * @file variable_object_keys.h
 * @brief Declaration for variable_object_keys function
 * 
 * This file contains ONLY the variable_object_keys declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_KEYS_H
#define VARIABLE_OBJECT_KEYS_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
char** variable_object_keys(const variable* object_var, size_t* count);

#endif /* VARIABLE_OBJECT_KEYS_H */
