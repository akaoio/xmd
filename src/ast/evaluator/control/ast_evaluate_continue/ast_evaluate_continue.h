/**
 * @file ast_evaluate_continue.h
 * @brief Declaration for ast_evaluate_continue function
 * 
 * This file contains ONLY the ast_evaluate_continue declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_CONTINUE_H
#define AST_EVALUATE_CONTINUE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_value*ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_CONTINUE_H */
