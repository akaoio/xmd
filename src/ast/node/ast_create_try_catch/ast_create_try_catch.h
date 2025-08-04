/**
 * @file ast_create_try_catch.h
 * @brief Header for ast_create_try_catch function
 * 
 * This file contains ONLY the ast_create_try_catch function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_CREATE_TRY_CATCH_H
#define XMD_AST_CREATE_TRY_CATCH_H

#include "../../../../../../include/ast.h"

/**
 * @brief Create try-catch AST node
 * @param try_block Block to execute that might throw
 * @param catch_var Variable name to capture exception in catch block
 * @param catch_block Block to execute if exception is thrown
 * @param loc Source location
 * @return New try-catch AST node or NULL on error
 */
ast_node* ast_create_try_catch(ast_node* try_block, const char* catch_var, ast_node* catch_block, source_location loc);

#endif /* XMD_AST_CREATE_TRY_CATCH_H */