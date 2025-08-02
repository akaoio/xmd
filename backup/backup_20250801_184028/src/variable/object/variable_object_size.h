/**
 * @file variable_object_size.h
 * @brief Declaration for variable_object_size function
 * 
 * This file contains ONLY the variable_object_size declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_SIZE_H
#define VARIABLE_OBJECT_SIZE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
size_t variable_object_size(const variable* object_var);

#endif /* VARIABLE_OBJECT_SIZE_H */
