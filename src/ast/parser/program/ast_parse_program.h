/**
 * @file ast_parse_program.h
 * @brief Declaration for ast_parse_program function
 * 
 * This file contains ONLY the ast_parse_program declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_PROGRAM_H
#define AST_PARSE_PROGRAM_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_parse_program(const char* input);

#endif /* AST_PARSE_PROGRAM_H */
