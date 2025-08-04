/**
 * @file ast_create_string_method.h
 * @brief Header for ast_create_string_method function
 */

#ifndef XMD_AST_CREATE_STRING_METHOD_H
#define XMD_AST_CREATE_STRING_METHOD_H

#include "ast.h"

/**
 * @brief Create string method call AST node
 * @param string_expr String expression
 * @param method_name Method name (upper, lower, split, etc.)
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_string_method(ast_node* string_expr, const char* method_name, source_location loc);

#endif /* XMD_AST_CREATE_STRING_METHOD_H */