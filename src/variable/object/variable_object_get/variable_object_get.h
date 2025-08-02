/**
 * @file variable_object_get.h
 * @brief Declaration for variable_object_get function
 * 
 * This file contains ONLY the variable_object_get declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_GET_H
#define VARIABLE_OBJECT_GET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_object_get(const variable* object_var, const char* key);

#endif /* VARIABLE_OBJECT_GET_H */
