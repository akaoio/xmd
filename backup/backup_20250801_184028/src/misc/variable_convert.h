/**
 * @file variable_convert.h
 * @brief Declaration for variable_convert function
 * 
 * This file contains ONLY the variable_convert declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CONVERT_H
#define VARIABLE_CONVERT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable*variable_convert(variable* var, variable_type target_type);

#endif /* VARIABLE_CONVERT_H */
