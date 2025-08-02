/**
 * @file ast_evaluator_create.h
 * @brief Declaration for ast_evaluator_create function
 * 
 * This file contains ONLY the ast_evaluator_create declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATOR_CREATE_H
#define AST_EVALUATOR_CREATE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_evaluator* ast_evaluator_create(store* variables, processor_context* ctx);

#endif /* AST_EVALUATOR_CREATE_H */
