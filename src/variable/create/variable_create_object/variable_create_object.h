/**
 * @file variable_create_object.h
 * @brief Declaration for variable_create_object function
 * 
 * This file contains ONLY the variable_create_object declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_CREATE_OBJECT_H
#define VARIABLE_CREATE_OBJECT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_create_object(void);

#endif /* VARIABLE_CREATE_OBJECT_H */
