/**
 * @file ast_functions_cleanup.h
 * @brief Declaration for ast_functions_cleanup function
 * 
 * This file contains ONLY the ast_functions_cleanup declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_FUNCTIONS_CLEANUP_H
#define AST_FUNCTIONS_CLEANUP_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
voidast_functions_cleanup(void);

#endif /* AST_FUNCTIONS_CLEANUP_H */
