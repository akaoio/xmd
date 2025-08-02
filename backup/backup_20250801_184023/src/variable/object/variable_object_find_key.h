/**
 * @file variable_object_find_key.h
 * @brief Declaration for variable_object_find_key function
 * 
 * This file contains ONLY the variable_object_find_key declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_FIND_KEY_H
#define VARIABLE_OBJECT_FIND_KEY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
size_t variable_object_find_key(const variable* object_var, const char* key);

#endif /* VARIABLE_OBJECT_FIND_KEY_H */
