/**
 * @file variable_get_number.h
 * @brief Declaration for variable_get_number function
 * 
 * This file contains ONLY the variable_get_number declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_GET_NUMBER_H
#define VARIABLE_GET_NUMBER_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
double variable_get_number(const variable* var);

#endif /* VARIABLE_GET_NUMBER_H */
