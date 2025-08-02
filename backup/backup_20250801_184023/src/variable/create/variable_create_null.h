/**
 * @file variable_create_null.h
 * @brief Declaration for variable_create_null function
 * 
 * This file contains ONLY the variable_create_null declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_NULL_H
#define VARIABLE_CREATE_NULL_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_null(void);

#endif /* VARIABLE_CREATE_NULL_H */
