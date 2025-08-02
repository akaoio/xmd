/**
 * @file ast_functions_init.h
 * @brief Declaration for ast_functions_init function
 * 
 * This file contains ONLY the ast_functions_init declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_FUNCTIONS_INIT_H
#define AST_FUNCTIONS_INIT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
void ast_functions_init(void);

#endif /* AST_FUNCTIONS_INIT_H */
