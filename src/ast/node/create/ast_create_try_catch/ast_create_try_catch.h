/**
 * @file ast_create_try_catch.h
 * @brief Header for ast_create_try_catch function
 */

#ifndef XMD_AST_CREATE_TRY_CATCH_H
#define XMD_AST_CREATE_TRY_CATCH_H

#include "ast.h"

/**
 * @brief Create try-catch AST node
 * @param try_block Try block AST node
 * @param catch_var Catch variable name
 * @param catch_block Catch block AST node  
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_try_catch(ast_node* try_block, const char* catch_var, ast_node* catch_block, source_location loc);

#endif /* XMD_AST_CREATE_TRY_CATCH_H */