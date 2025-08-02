/**
 * @file ast_evaluate_assignment.h
 * @brief Declaration for ast_evaluate_assignment function
 * 
 * This file contains ONLY the ast_evaluate_assignment declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_ASSIGNMENT_H
#define AST_EVALUATE_ASSIGNMENT_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
int ast_evaluate_assignment(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_ASSIGNMENT_H */
