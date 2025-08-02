/**
 * @file variable_create_array.h
 * @brief Declaration for variable_create_array function
 * 
 * This file contains ONLY the variable_create_array declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_ARRAY_H
#define VARIABLE_CREATE_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_array(void);

#endif /* VARIABLE_CREATE_ARRAY_H */
