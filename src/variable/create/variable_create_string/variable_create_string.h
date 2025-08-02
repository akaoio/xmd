/**
 * @file variable_create_string.h
 * @brief Declaration for variable_create_string function
 * 
 * This file contains ONLY the variable_create_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_STRING_H
#define VARIABLE_CREATE_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_string(const char* value);

#endif /* VARIABLE_CREATE_STRING_H */
