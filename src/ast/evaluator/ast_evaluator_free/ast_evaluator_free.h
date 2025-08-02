/**
 * @file ast_evaluator_free.h
 * @brief Declaration for ast_evaluator_free function
 * 
 * This file contains ONLY the ast_evaluator_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_EVALUATOR_FREE_H
#define AST_EVALUATOR_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
void ast_evaluator_free(ast_evaluator* evaluator);

#endif /* AST_EVALUATOR_FREE_H */
