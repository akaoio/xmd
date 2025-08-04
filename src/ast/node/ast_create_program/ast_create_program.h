/**
 * @file ast_create_program.h
 * @brief Declaration for ast_create_program function
 * 
 * This file contains ONLY the ast_create_program declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_PROGRAM_H
#define AST_CREATE_PROGRAM_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_program(void);

#endif /* AST_CREATE_PROGRAM_H */
