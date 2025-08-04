/**
 * @file ast_create_throw.h
 * @brief Header for ast_create_throw function
 * 
 * This file contains ONLY the ast_create_throw function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_CREATE_THROW_H
#define XMD_AST_CREATE_THROW_H

#include "../../../../../../include/ast.h"

/**
 * @brief Create throw statement AST node
 * @param exception Expression to throw as exception
 * @param loc Source location
 * @return New throw AST node or NULL on error
 */
ast_node* ast_create_throw(ast_node* exception, source_location loc);

#endif /* XMD_AST_CREATE_THROW_H */