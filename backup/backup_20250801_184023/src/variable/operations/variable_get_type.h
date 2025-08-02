/**
 * @file variable_get_type.h
 * @brief Declaration for variable_get_type function
 * 
 * This file contains ONLY the variable_get_type declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_GET_TYPE_H
#define VARIABLE_GET_TYPE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable_type variable_get_type(const variable* var);

#endif /* VARIABLE_GET_TYPE_H */
