/**
 * @file ast_create_string_method.h
 * @brief Header for ast_create_string_method function
 * 
 * This file contains ONLY the ast_create_string_method function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_CREATE_STRING_METHOD_H
#define XMD_AST_CREATE_STRING_METHOD_H

#include "../../../../../../include/ast.h"

/**
 * @brief Create string method call AST node
 * @param string_expr String expression to call method on
 * @param method_name Method name (upper, lower, split, join, trim)
 * @param loc Source location
 * @return New string method AST node or NULL on error
 */
ast_node* ast_create_string_method(ast_node* string_expr, const char* method_name, source_location loc);

#endif /* XMD_AST_CREATE_STRING_METHOD_H */