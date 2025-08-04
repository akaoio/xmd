/**
 * @file ast_value_create_object.h
 * @brief Declaration for ast_value_create_object function
 * 
 * This file contains ONLY the ast_value_create_object declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_VALUE_CREATE_OBJECT_H
#define AST_VALUE_CREATE_OBJECT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */
typedef struct ast_value ast_value;

/* Function declaration */
ast_value* ast_value_create_object(void);

#endif /* AST_VALUE_CREATE_OBJECT_H */