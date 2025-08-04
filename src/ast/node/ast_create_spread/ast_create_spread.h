/**
 * @file ast_create_spread.h
 * @brief Header for ast_create_spread function
 */

#ifndef AST_CREATE_SPREAD_H
#define AST_CREATE_SPREAD_H

#include "ast.h"
#include <stdbool.h>

ast_node* ast_create_spread(ast_node* expression, bool in_array, bool in_object, source_location loc);

#endif