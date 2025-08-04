/**
 * @file ast_parse_await.h
 *
 * @brief Header for ast_parse_await function
 * 
 * This file contains ONLY declarations for ast_parse_await.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_AWAIT_H
#define AST_PARSE_AWAIT_H

#include "ast.h"

ast_node* ast_parse_await(parser_state* parser);

#endif /* AST_PARSE_AWAIT_H */