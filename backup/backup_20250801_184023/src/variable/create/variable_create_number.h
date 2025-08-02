/**
 * @file variable_create_number.h
 * @brief Declaration for variable_create_number function
 * 
 * This file contains ONLY the variable_create_number declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_NUMBER_H
#define VARIABLE_CREATE_NUMBER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_number(double value);

#endif /* VARIABLE_CREATE_NUMBER_H */
