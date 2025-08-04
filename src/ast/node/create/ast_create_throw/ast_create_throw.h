/**
 * @file ast_create_throw.h
 * @brief Header for ast_create_throw function
 */

#ifndef XMD_AST_CREATE_THROW_H
#define XMD_AST_CREATE_THROW_H

#include "ast.h"

/**
 * @brief Create throw statement AST node
 * @param exception Exception expression to throw
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_throw(ast_node* exception, source_location loc);

#endif /* XMD_AST_CREATE_THROW_H */