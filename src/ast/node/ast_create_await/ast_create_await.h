/**
 * @file ast_create_await.h
 *
 * @brief Header for ast_create_await function
 * 
 * This file contains ONLY declarations for ast_create_await.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_AWAIT_H
#define AST_CREATE_AWAIT_H

#include "ast.h"

ast_node* ast_create_await(ast_node* expression, source_location loc);

#endif /* AST_CREATE_AWAIT_H */