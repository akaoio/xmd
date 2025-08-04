/**
 * @file ast_create_lambda.h
 * @brief Header for ast_create_lambda function
 * 
 * This file contains ONLY the ast_create_lambda function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_CREATE_LAMBDA_H
#define XMD_AST_CREATE_LAMBDA_H

#include "../../../../../../include/ast.h"

/**
 * @brief Create lambda function AST node
 * @param parameters Array of parameter names
 * @param parameter_count Number of parameters
 * @param body Lambda body expression
 * @param loc Source location
 * @return New lambda AST node or NULL on error
 */
ast_node* ast_create_lambda(char** parameters, size_t parameter_count, ast_node* body, source_location loc);

#endif /* XMD_AST_CREATE_LAMBDA_H */