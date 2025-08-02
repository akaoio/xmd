/**
 * @file ast_evaluate_program_node.h
 * @brief Declaration for ast_evaluate_program_node function
 * 
 * This file contains ONLY the ast_evaluate_program_node declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATE_PROGRAM_NODE_H
#define AST_EVALUATE_PROGRAM_NODE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_value*ast_evaluate_program_node(ast_node* node, ast_evaluator* evaluator);

#endif /* AST_EVALUATE_PROGRAM_NODE_H */
