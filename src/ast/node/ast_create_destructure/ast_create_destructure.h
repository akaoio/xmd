/**
 * @file ast_create_destructure.h
 * @brief Header for ast_create_destructure function
 */

#ifndef AST_CREATE_DESTRUCTURE_H
#define AST_CREATE_DESTRUCTURE_H

#include "ast.h"
#include <stdbool.h>

ast_node* ast_create_destructure(char** target_names, size_t target_count, 
                                ast_node* source_expr, bool is_object, 
                                const char* rest_name, source_location loc);

#endif