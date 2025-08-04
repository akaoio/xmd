/**
 * @file ast_parse_lambda.h
 * @brief Header for ast_parse_lambda function
 * 
 * This file contains ONLY the ast_parse_lambda function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_PARSE_LAMBDA_H
#define XMD_AST_PARSE_LAMBDA_H

#include "../../../../../../include/ast.h"

/**
 * @brief Parse lambda function expression
 * @param pos Pointer to current position in input (will be advanced)
 * @return Lambda AST node or NULL if not a lambda expression
 */
ast_node* ast_parse_lambda(const char** pos);

#endif /* XMD_AST_PARSE_LAMBDA_H */